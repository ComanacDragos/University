"""
The client sends a domain name taken from the command line (Ex: www.google.com) to the server.
The server opens a TCP connection to the IP address corresponding to the received domain name on port 80 (called HTTP-Srv).
It sends on the TCP connection the string: “GET / HTTP/1.0\n\n” and relays the answer back to the client.
When HTTP-Srv closes connection to the server, the server closes the connection to the client at its turn.
"""

import socket
import sys

try:
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    clientSocket.connect((sys.argv[1], int(sys.argv[2])))
except IndexError as msg:
    print(msg)
    exit(1)
except socket.error as msg:
    print(msg.strerror)
    exit(1)

try:
    clientSocket.sendall(bytes(sys.argv[3], 'ascii'), 0)

    answer = clientSocket.recv(1024)

    print(answer.decode('ascii'))
except socket.error as msg:
    print(msg.strerror)

clientSocket.close()
