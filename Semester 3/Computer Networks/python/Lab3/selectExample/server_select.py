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


def sendAll(message, sock, master, ignoreList):
    for peer in master:
        if peer not in ignoreList:
            sock.sendall(bytes(message, 'ascii'))


serverAddress = ("", -1)
try:
    serverAddress = (sys.argv[1], int(sys.argv[2]))
except Exception as msg:
    print(msg)
    exit(1)

serverSocket = None
master = []
try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.bind(serverAddress)
    serverSocket.listen(10)
except socket.error as msg:
    print(msg.strerror)
    exit(1)

master.append(serverSocket)
print('Listening...')
while True:
    try:
        ready, _, _ = select.select(master, [], [])
    except select.error or socket.error as msg:
        print("ERROR", msg.strerror)
        continue

    for sock in ready:
        if sock == serverSocket:
            try:
                clientSocket, clientAddress = serverSocket.accept()
                print(f"Incoming connection from {clientSocket.getpeername()}")
                master.append(clientSocket)
            except socket.error as msg:
                print(socket.error)
        else:
            message = ""
            try:
                response = sock.recv(1024)

                message = response.decode('ascii')

                if message == 'QUIT' or message == '':
                    master.remove(sock)
                    message = f"<server> {sock.getpeername()[0]}:{sock.getpeername()[1]} disconnected"
                    sock.close()
                else:
                    message = f"<{sock.getpeername()[0]}:{sock.getpeername()[1]}> {response.decode('ascii')}"

            except socket.error as msg:
                print(msg.strerror)
                master.remove(sock)
                sock.close()
                message = f"<server> {sock.getpeername()[0]}:{sock.getpeername()[1]} disconnected abruptly"

            print(message)
            toBeRemoved = []
            for peer in master:
                if peer not in [serverSocket, sock]:
                    try:
                        peer.sendall(bytes(message, 'ascii'))
                    except socket.error as msg:
                        print(msg.strerror)
                        toBeRemoved.append(peer)

            message = ""
            for peer in toBeRemoved:
                master.remove(peer)
                message += f"<server> {peer.getpeername()[0]}:{peer.getpeername()[1]} disconnected abruptly"

            if message != "":
                sendAll(message, serverSocket, master, [serverSocket])



