import socket
import sys
import time
import threading
from datetime import datetime
from collections import deque
import re
from copy import deepcopy
import random

allowedMissedBroadcasts = 3

broadcastLock = threading.Lock()
malformedDataLock = threading.Lock()
malformedData = deque(maxlen=5)

peers = []
answeredTime = []
answeredDate = []

peersLock = threading.Lock()
answeredDateLock = threading.Lock()
answeredTimeLock = threading.Lock()


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
    global broadcastLock, peers, peersLock, answeredTime, answeredTimeLock, allowedMissedBroadcasts
    start = 0
    end = 0
    while True:
        try:
            broadcastLock.acquire()
            broadcastSocket.sendto(b'TIMEQUERY', ('<broadcast>', 7777))
            broadcastLock.release()
        except socket.error as msg:
            print('Error on sending timequery', msg.strerror)

        time.sleep(3 - (end - start))

        start = time.time()

        inactivePeers = []
        peersLock.acquire()
        answeredTimeLock.acquire()
        for p in peers:
            if p.address in answeredTime:
                p.missedBroadcasts = 0
            else:
                p.missedBroadcasts += 1
                if p.missedBroadcasts == allowedMissedBroadcasts:
                    inactivePeers.append(p)
        answeredTime = []
        answeredTimeLock.release()

        for p in inactivePeers:
            peers.remove(p)
        peersLock.release()
        end = time.time()


def tenSecondsEvent(broadcastSocket):
    global broadcastLock, answeredDateLock, answeredDate
    start = 0
    end = 0
    while True:
        try:
            broadcastLock.acquire()
            broadcastSocket.sendto(b'DATEQUERY', ('<broadcast>', 7777))
            broadcastLock.release()
        except socket.error as msg:
            print('Error on sending datequery', msg.strerror)

        time.sleep(10 - (end - start))

        start = time.time()

        inactivePeers = []
        peersLock.acquire()
        answeredDateLock.acquire()
        for p in peers:
            if p.address in answeredDate:
                p.missedBroadcasts = 0
            else:
                p.missedBroadcasts += 1
                if p.missedBroadcasts == allowedMissedBroadcasts:
                    inactivePeers.append(p)
        answeredDate = []
        answeredDateLock.release()

        for p in inactivePeers:
            peers.remove(p)
        peersLock.release()
        end = time.time()


def responseEvent(broadcastSocket):
    global malformedData, malformedDataLock, peers, peersLock, answeredTime, answeredDate, answeredDateLock, answeredTimeLock
    while True:
        response = ""
        fromAddress = ("", -1)
        try:
            response, fromAddress = broadcastSocket.recvfrom(1024)
        except socket.error as msg:
            print('Error on receiving', msg.strerror)

        timeCond = re.search('^TIME [0-9]{2}:[0-9]{2}:[0-9]{2}', response.decode('ascii')) is None
        dateCond = re.search('^DATE [0-9]{2}:[0-9]{2}:[0-9]{4}', response.decode('ascii')) is None

        if timeCond and dateCond:
            malformedDataLock.acquire()
            malformedData.appendleft(response.decode('ascii'))
            localMalformedData = deepcopy(malformedData)
            malformedDataLock.release()

            peersLock.acquire()
            localPeers = deepcopy(peers)
            peersLock.release()

            for p in localPeers:
                print(p)
            print()

            print('Malformed data:')
            for data in localMalformedData:
                print(data)

            continue

        tokens = response.decode('ascii').split()
        peersLock.acquire()
        if fromAddress not in peers:
            peer = Peer(fromAddress)
            if tokens[0] == "TIME":
                peer.time = tokens[1]

                answeredTimeLock.acquire()
                answeredTime.append(peer)
                answeredTimeLock.release()

            elif tokens[0] == "DATE":
                peer.date = tokens[1]

                answeredDateLock.acquire()
                answeredDate.append(peer)
                answeredDateLock.release()

            peers.append(peer)
        else:
            for peer in peers:
                if peer.address == fromAddress:
                    if tokens[0] == "TIME":
                        peer.time = tokens[1]

                        answeredTimeLock.acquire()
                        answeredTime.append(peer)
                        answeredTimeLock.release()

                    elif tokens[0] == "DATE":
                        peer.date = tokens[1]

                        answeredDateLock.acquire()
                        answeredDate.append(peer)
                        answeredDateLock.release()
                    break

        localPeers = deepcopy(peers)
        peersLock.release()

        clearConsole()

        for p in localPeers:
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

        broadcastSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        broadcastSocket.bind((sys.argv[1], 1234 + random.randint(1, 60000)))
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

        broadcastSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        broadcastSocket.bind(("", 7777))

        responseSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    except socket.error as msg:
        print(msg.strerror)
        exit(1)
    while True:
        try:
            message, addressFrom = broadcastSocket.recvfrom(1024)
        except socket.error as msg:
            print('Error on receiving', msg.strerror)
            continue

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

        try:
            responseSocket.sendto(bytes(response, 'ascii'), addressFrom)
        except socket.error as msg:
            print('Error on sending', msg.strerror)


main()
