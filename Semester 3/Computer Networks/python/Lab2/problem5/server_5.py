"""
The client sends a domain name taken from the command line (Ex: www.google.com) to the server.
The server opens a TCP connection to the IP address corresponding to the received domain name on port 80 (called HTTP-Srv).
It sends on the TCP connection the string: “GET / HTTP/1.0\n\n” and relays the answer back to the client.
When HTTP-Srv closes connection to the server, the server closes the connection to the client at its turn.
"""

import socket
import sys
import multiprocessing


def worker(clientSocket):
    print(f"Incoming connection from {clientSocket.getpeername()}")

    try:
        domainName = clientSocket.recv(1024)
        domainName = domainName.decode('ascii')

        responseSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print(f"Waiting to connect to {domainName}")
        responseSocket.connect((domainName, 80))

        responseSocket.sendall(bytes("GET / HTTP/1.0\n\n", 'ascii'))

        response = responseSocket.recv(1024)

        clientSocket.sendall(response)

        clientSocket.close()
    except socket.error as msg:
        print(msg.strerror)
    exit(0)


def main():
    try:
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.bind((sys.argv[1], int(sys.argv[2])))
        serverSocket.listen(10)
    except IndexError as msg:
        print(msg)
        exit(1)
    except socket.error as msg:
        print(msg.strerror)
        exit(1)

    print('Listening...')
    while True:
        clientSocket, clientAddress = serverSocket.accept()

        multiprocessing.Process(target=worker, args=(clientSocket,)).start()

if __name__ == '__main__':
    main()
