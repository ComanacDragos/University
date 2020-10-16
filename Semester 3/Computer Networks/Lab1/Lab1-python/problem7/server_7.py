import os
import struct
import socket
import signal

clientNumber = 0

print(f"Server PID {os.getpid()}")


def worker(clientSocket, clientId):
    print(f'Incoming connection from {clientSocket.getpeername()} in {os.getpid()}')

    message = f'Welcome {clientId}'

    try:
        clientSocket.sendall(bytes(message, 'ascii'))

        stringLength = struct.unpack('!I', clientSocket.recv(4))[0]
        string = clientSocket.recv(stringLength).decode('ascii')

        start = struct.unpack('!I', clientSocket.recv(4))[0]
        length = struct.unpack('!I', clientSocket.recv(4))[0]
    except socket.error as msg:
        print('Error ', msg.strerror)
        exit(-1)

    if start + length <= len(string) and length > 0 and start >= 0:
        substring = string[start:start + length]
    else:
        length = -1

    try:
        clientSocket.sendall(struct.pack('!i', length))
        if length != -1:
            clientSocket.send(bytes(substring, 'ascii'))
    except socket.error as msg:
        print('Error ', msg.strerror)
        exit(-1)
    exit(0)


def endServerHandler(signum, frame):
    global clientNumber

    print(f'Waiting for {clientNumber}')
    for i in range(clientNumber):
        os.wait()
    print('Done waiting\nExiting...\n')
    exit(0)


def main():
    global clientNumber

    signal.signal(signal.SIGINT, endServerHandler)

    try:
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.bind(('192.168.0.115', 1234))
        serverSocket.listen(5)
    except socket.error as msg:
        print('Error ', msg.strerror)
        exit(-1)

    print('Listening for connections')
    while True:
        clientSocket, clientAddress = serverSocket.accept()

        clientNumber += 1
        if os.fork() == 0:
            worker(clientSocket, clientNumber)


main()
