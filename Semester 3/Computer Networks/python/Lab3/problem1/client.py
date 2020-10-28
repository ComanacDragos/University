"""
The client sends periodical PING datagrams with a random content to a <server> and <port> specified in command line.
The server returns back (echoes) the same packets (content).
 The client checks the content of the received packets to match what was sent and computes the round trip time and
  displays it to the user – for each sent packet.
"""

import sys
import socket
import os

address = (sys.argv[1], int(sys.argv[2]))

clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

count = 10
while count > 0:
    count -= 1
    message = input('>> ')

    if message == 'exit':
        break

    clientSocket.sendto(bytes(message, 'ascii'), address)

    response = clientSocket.recvfrom(1024)

    print(response[0].decode('ascii'), response[1])

clientSocket.close()