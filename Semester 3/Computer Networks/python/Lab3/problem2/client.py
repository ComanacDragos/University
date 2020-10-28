import socket
import random
import time
import struct
import sys

serverAddress = None
clientSocket = None

left = 1
right = 1000

try:
    serverAddress = (sys.argv[1], int(sys.argv[2]))
except Exception as msg:
    print(msg)
    exit(1)

try:
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
except socket.error as msg:
    print(msg)
    exit(1)

while True:
    myNumber = random.randint(left, right)

    clientSocket.sendto(struct.pack('!i', myNumber), serverAddress)
    response, incomingAddress = clientSocket.recvfrom(1)

    while incomingAddress != serverAddress:
        print('Bad sender')
        response, incomingAddress = clientSocket.recvfrom(1)

    response = response.decode('ascii')

    if response == '<':
        left = myNumber + 1
        print(f"{myNumber} is smaller than SRI")
    elif response == '>':
        right = myNumber - 1
        print(f"{myNumber} is larger than SRI")
    elif response == '=':
        print('You won', myNumber)
        break
    else:
        print('You lost', myNumber)
        break

    time.sleep(1)

clientSocket.close()


