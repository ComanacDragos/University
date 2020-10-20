"""
The client sends to the server two arrays of integers.
The server returns an arrays containing the common numbers found in both arrays.
"""

import socket
import struct
import os
import signal

clientCount = 0
serverSocket = None

print(f'Process id {os.getpid()}')

def handler(signum, frame):
    global clientCount

    #if serverSocket is not None:
    #    serverSocket.close()

    for i in range(clientCount):
        os.wait()
    print('Exiting...')
    exit(0)


def worker(clientSocket, clientId):
    print(f"Connected from {clientSocket.getpeername()}, to {os.getpid()}")

    message = f'Welcome {clientId}'

    try:
        clientSocket.send(bytes(message, 'ascii'))

        length1 = struct.unpack('!I', clientSocket.recv(4))[0]
        length2 = struct.unpack('!I', clientSocket.recv(4))[0]

        array1 = []
        array2 = []
        for i in range(length1):
            array1.append(struct.unpack('!i', clientSocket.recv(4))[0])

        for i in range(length2):
            array2.append(struct.unpack('!i', clientSocket.recv(4))[0])

        intersection = [x for x in array1 if x in array2]

        toBeSent = []
        for x in intersection:
            if x not in toBeSent:
                toBeSent.append(x)

        clientSocket.sendall(struct.pack('!I', len(toBeSent)))

        for x in toBeSent:
            clientSocket.sendall(struct.pack('!i', x))

    except socket.error as msg:
        print("Error: ", msg.strerror)

    clientSocket.close()
    exit(0)


def main():
    global clientCount, serverSocket
    try:
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.bind(('192.168.0.115', 1234))
        serverSocket.listen(5)
    except socket.error as msg:
        print("Error", msg.strerror)
        exit(1)

    try:
        signal.signal(signal.SIGINT, handler)
    except Exception as msg:
        print("Signal error: ", msg)
        exit(1)

    print('Listening....')
    while True:
        try:
            clientSocket, _ = serverSocket.accept()

            clientCount += 1
            if os.fork() == 0:
                worker(clientSocket, clientCount)
        except Exception as msg:
            print('Error: ', msg)

if __name__ == '__main__':
    main()