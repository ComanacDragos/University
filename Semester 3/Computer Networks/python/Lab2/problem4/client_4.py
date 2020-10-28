"""
The clients send an integer number N and an array of N float values.
 The server will merge sort the numbers received from all clients until it gets an empty array of floats (N=0).
 The server returns to each client the size of the merge-sorted array
  followed by the merge-sorted arrays of all floats from all clients.
"""

import socket
import random
import struct

MIN_SIZE = 1
MAX_SIZE = 10
MIN_VAL = -10
MAX_VAL = 10
ROUND = 2

try:
    clientSocket = socket.create_connection(('localhost', 1234))
except socket.error as msg:
    print("Error: " + msg.strerror)
    exit(-1)

N = int(input("Give number of floats to send: "))

try:
    msg = clientSocket.recv(1024).decode('ascii')
    print(msg)

    clientSocket.sendall(struct.pack('!I', N))
except socket.error as msg:
    print("Error on sending N:  " + msg.strerror)
    clientSocket.close()
    exit(-2)

if N != 0:
    for i in range(N):
        f = struct.pack('!f', round(random.uniform(MIN_VAL, MAX_VAL), ROUND))

        try:
            clientSocket.sendall(f)
        except socket.error as msg:
            print(msg.strerror)
            clientSocket.close()
            exit(-2)

        print(round(struct.unpack('!f', f)[0], ROUND), end=' ')
    print()

try:
    N = struct.unpack('!I', clientSocket.recv(4))[0]

    print(f"Received {N} numbers")

    for i in range(N):
        f = round(struct.unpack('!f', clientSocket.recv(4))[0], ROUND)
        print(f)
except socket.error as msg:
    print(msg.strerror)
    clientSocket.close()
    exit(-2)