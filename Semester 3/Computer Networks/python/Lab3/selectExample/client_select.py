"""
This example presents an implementation of a client-server chat application working in the command line in an IRC style
application with only one room. The server accepts multiple TCP clients and relays messages passed by each client to
all other connected clients. The client needs to be able to:

·       read messages from standard input and pass them to the server;

·       read messages relayed from the server and display them to the user;



The motivation of using select lies here in the fact that there are multiple descriptors that need to be watched by both
the client and the server. The server also needs a shared state approach where creating a new process to handle each
client would only make things complicated.
"""

import socket
import sys
import select

serverAddress = ("", -1)
try:
    serverAddress = (sys.argv[1], int(sys.argv[2]))
except Exception as msg:
    print(msg)
    exit(1)

clientSocket = None
try:
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.connect(serverAddress)
except socket.error as msg:
    print(msg.strerror)
    exit(1)

master = [sys.stdin, clientSocket]

running = True
while running:
    ready, _, _ = select.select(master, [], [])

    for sock in ready:
        if sock == sys.stdin:
            message = input()
            clientSocket.sendall(bytes(message, 'ascii'))
            if message == 'QUIT':
                running = False
                break
        else:
            message = clientSocket.recv(1024).decode('ascii')
            print(message)

