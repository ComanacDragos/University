import socket
import sys
import time
import threading
from datetime import datetime
from collections import deque
import re
from copy import deepcopy

broadcastLock = threading.Lock()
malformedDataLock = threading.Lock()
malformedData = deque(maxlen=5)


def clearConsole():
    print(100 * '\n')


class Peer:
    def __init__(self, address):
        self.address = address
        self.time = None
        self.date = None
        self.missedBroadcasts = 0

    def __eq__(self, other):
        return self.address == other

    def __str__(self):
        return f"{self.address[0]}:{self.address[1]}\t\tTIME {self.time} DATE {self.date}"


def threeSecondsEvent(broadcastSocket):
    global broadcastLock
    while True:
        broadcastLock.acquire()
        broadcastSocket.sendto(b'TIMEQUERY', ('<broadcast>', 7777))
        broadcastLock.release()

        time.sleep(3)


def tenSecondsEvent(broadcastSocket):
    global broadcastLock
    while True:
        broadcastLock.acquire()
        broadcastSocket.sendto(b'DATEQUERY', ('<broadcast>', 7777))
        broadcastLock.release()

        time.sleep(10)


def responseEvent(broadcastSocket):
    global malformedData, malformedDataLock
    peers = []
    while True:
        response, fromAddress = broadcastSocket.recvfrom(1024)

        timeCond = re.search('^TIME [0-9]{2}:[0-9]{2}:[0-9]{2}', response.decode('ascii')) is None
        dateCond = re.search('^DATE [0-9]{2}:[0-9]{2}:[0-9]{4}', response.decode('ascii')) is None

        if timeCond and dateCond:
            malformedDataLock.acquire()
            malformedData.appendleft(response.decode('ascii'))
            localMalformedData = deepcopy(malformedData)
            malformedDataLock.release()

            for p in peers:
                print(p)
            print()

            print('Malformed data:')
            for data in localMalformedData:
                print(data)

            continue

        tokens = response.decode('ascii').split()
        if fromAddress not in peers:
            peer = Peer(fromAddress)
            if tokens[0] == "TIME":
                peer.time = tokens[1]
            elif tokens[0] == "DATE":
                peer.date = tokens[1]
            peers.append(peer)
        else:
            for peer in peers:
                if peer.address == fromAddress:
                    if tokens[0] == "TIME":
                        peer.time = tokens[1]
                    elif tokens[0] == "DATE":
                        peer.date = tokens[1]
                    break

        inactivePeers = []
        for p in peers:
            if p.address == fromAddress:
                p.missedBroadcasts = 0
            else:
                p.missedBroadcasts += 1
                if p.missedBroadcasts == 3:
                    inactivePeers.append(p)

        for p in inactivePeers:
            peers.remove(p)

        clearConsole()
        for p in peers:
            print(p)
        print()

        malformedDataLock.acquire()
        localMalformedData = deepcopy(malformedData)
        malformedDataLock.release()
        print('Malformed data:')
        for data in localMalformedData:
            print(data)


def setupEvents():
    try:
        broadcastSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        broadcastSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        broadcastSocket.bind((sys.argv[1], 1234))

    except socket.error as msg:
        print(msg.strerror)
        exit(1)

    threading.Thread(target=tenSecondsEvent, args=(broadcastSocket,)).start()
    threading.Thread(target=threeSecondsEvent, args=(broadcastSocket,)).start()
    threading.Thread(target=responseEvent, args=(broadcastSocket,)).start()


def main():
    global malformedDataLock, malformedData
    setupEvents()
    broadcastSocket = None
    responseSocket = None
    try:
        broadcastSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        broadcastSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        broadcastSocket.bind(("", 7777))

        responseSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except socket.error as msg:
        print(msg.strerror)
        exit(1)
    while True:
        message, addressFrom = broadcastSocket.recvfrom(1024)
        message = message.decode('ascii').replace('\n', '')

        if message == 'TIMEQUERY':
            response = f"TIME {datetime.now().strftime('%H:%M:%S')}"
        elif message == 'DATEQUERY':
            response = f"DATE {datetime.now().strftime('%d:%m:%Y')}"
        else:
            malformedDataLock.acquire()
            malformedData.appendleft(f"{addressFrom[0]}:{addressFrom[1]}\t\t{message}")
            malformedDataLock.release()
            continue

        responseSocket.sendto(bytes(response, 'ascii'), addressFrom)


main()
