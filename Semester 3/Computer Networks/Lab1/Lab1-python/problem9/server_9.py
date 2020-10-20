"""
The client sends to the server two arrays of numbers.
 The server returns to the client a list
of numbers that are present in the first arrays but not in the second.
"""

from multiprocessing import Pool, Process
import socket
import struct
import signal

processes = []


def receive_array(clientSocket):
    arr = []
    try:
        len = struct.unpack('!I', clientSocket.recv(4))[0]

        arr = []
        for i in range(len):
            arr.append(struct.unpack('!i', clientSocket.recv(4))[0])

    except socket.error as msg:
        print("Error: ", msg.strerror)
    finally:
        return arr


def worker(clientSocket, clientCount):
    print("Starting: ", clientSocket.getpeername(), clientCount)

    message = f"Welcome {clientCount}"

    v1 = []
    v2 = []

    try:
        clientSocket.sendall(bytes(message, 'ascii'))

        v1 = receive_array(clientSocket)
        v2 = receive_array(clientSocket)
    except socket.error as msg:
        print("Error", msg.strerror)

    difference = [x for x in v1 if x not in v2]
    sent = []
    for i in difference:
        if i not in sent:
            sent.append(i)

    try:
        clientSocket.sendall(struct.pack('!I', len(sent)))

        for i in sent:
            clientSocket.sendall(struct.pack('!i', i))

    except socket.error as msg:
        print("error", msg.strerror)

    exit(0)


def handler(signum, frame):
    global processes

    print("Joining processes")
    for p in processes:
        p.join()
    print("Exiting...")
    exit(0)


def main():
    global processes, clientCount
    try:
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.bind(("192.168.0.115", 1234))
        serverSocket.listen(5)
    except socket.error as msg:
        print("Error:", msg.strerror)
        exit(1)

    #signal.signal(signal.SIGINT, handler)

    clientCount = 0
    print("Listening...")
    while True:
        clientSocket, clientAddress = serverSocket.accept()
        clientCount += 1

        p = Process(target=worker, args=(clientSocket, clientCount))
        p.start()

        print("Incoming connection from", clientAddress)
        processes.append(p)


if __name__ == '__main__':
    main()
