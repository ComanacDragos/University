import socket
import struct
import sys
import random

myAddress = None
serverSocket = None
try:
    myAddress = (sys.argv[1], int(sys.argv[2]))
except Exception as msg:
    print(msg)
    exit(1)

SRI = random.randint(1, 1000)
print(f"SRF {SRI}")
try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSocket.bind(myAddress)
except socket.error as msg:
    print(msg.strerror)
    exit(1)

addresses = set()
winner = None

print("Listening...")
while winner is None:
    number, incomingAddress = serverSocket.recvfrom(4)
    number = struct.unpack('!i', number)[0]
    print(f'Received from {incomingAddress} the number {number}')

    addresses.add(incomingAddress)

    if number < SRI:
        serverSocket.sendto(b'<', incomingAddress)
    elif number > SRI:
        serverSocket.sendto(b'>', incomingAddress)
    else:
        winner = incomingAddress

for address in addresses:
    if address == winner:
        serverSocket.sendto(b'=', address)
    else:
        serverSocket.sendto(b'!', address)

serverSocket.close()