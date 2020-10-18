"""
The client sends to the server two arrays of integers.
The server returns an arrays containing the common numbers found in both arrays.
"""

import socket
import struct

try:
    clientSocket = socket.create_connection(('192.168.0.157', 1234))
except socket.error as msg:
    print('Error on connection', msg.strerror)
    exit(1)

try:
    print(clientSocket.recv(1024).decode('ascii'))
except socket.error as msg:
    print('Error on receiving: ', msg.strerror)

length1 = int(input('Give first length: '))

array1 = []
for i in range(length1):
    array1.append(int(input('Give element: ')))

length2 = int(input('Give second length: '))

array2 = []
for i in range(length2):
    array2.append(int(input('Give element: ')))

try:
    clientSocket.sendall(struct.pack('!I', length1))
    clientSocket.sendall(struct.pack('!I', length2))

    for x in array1:
        clientSocket.sendall(struct.pack('!i', x))

    for x in array2:
        clientSocket.sendall(struct.pack('!i', x))
except socket.error as msg:
    print('Error on sending ', msg.strerror)

try:
    length = struct.unpack('!I', clientSocket.recv(4))[0]
    print('Received: ', length)
    for i in range(length):
        print(struct.unpack('!i', clientSocket.recv(4))[0], end=' ')
    print()

    clientSocket.close()
except socket.error as msg:
    print('Error ', msg.strerror)


