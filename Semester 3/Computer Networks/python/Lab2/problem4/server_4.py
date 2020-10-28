"""
The clients send an integer number N and an array of N float values.
 The server will merge sort the numbers received from all clients until it gets an empty array of floats (N=0).
 The server returns to each client the size of the merge-sorted array
  followed by the merge-sorted arrays of all floats from all clients.
"""

import threading
import socket
import struct

threads = []
stopEvent = threading.Event()
stopEvent.clear()
floats = []
myLock = threading.Lock()
ROUND = 2
threadCount = []


def worker(clientSocket, clientCount):
    global floats, myLock, ROUND

    print("Connected: ", clientSocket.getpeername())

    message = f'Welcome {clientCount}'

    localFloats = []
    try:
        clientSocket.sendall(bytes(message, 'ascii'))

        N = struct.unpack('!I', clientSocket.recv(4))[0]

        string = f'Received {N} from {clientSocket.getpeername()}\n'

        for i in range(N):
            f = round(struct.unpack('!f', clientSocket.recv(4))[0], ROUND)
            string += str(f) + ', '
            localFloats.append(f)
        print(string)
    except socket.error as msg:
        print("Error: ", msg.strerror)

    if N != 0:
        myLock.acquire()
        floats += localFloats
        floats.sort()
        myLock.release()

        stopEvent.wait()
    else:
        stopEvent.set()

    try:
        clientSocket.sendall(struct.pack('!I', len(floats)))
        for i in floats:
            clientSocket.sendall(struct.pack('!f', i))
    except socket.error as msg:
        print("Error: ", msg)


def resetServer():
    global threads, stopEvent, floats, myLock, threadCount

    while True:
        stopEvent.wait()

        for t in threads:
            t.join()

        print("All threads released, resetting...")

        myLock.acquire()
        threads = []
        stopEvent.clear()
        floats = []
        threadCount = []
        myLock.release()


def main():
    global threads, threadCount
    try:
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.bind(('localhost', 1234))
        serverSocket.listen(5)
    except socket.error as msg:
        print("Sock Error: ", msg.strerror)
        exit(-1)

    t = threading.Thread(target=resetServer, daemon=True)
    t.start()

    print("Listening for connections...")
    while True:
        clientSocket, clientAddr = serverSocket.accept()

        threadCount.append(len(threadCount))
        t = threading.Thread(target=worker, args=(clientSocket, threadCount[len(threadCount) - 1]))
        threads.append(t)

        t.start()

main()