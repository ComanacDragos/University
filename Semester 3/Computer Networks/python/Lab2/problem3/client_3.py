import socket
import struct
import random

try:
    clientSocket = socket.create_connection(('localhost', 1234))
except socket.error as msg:
    print("Error: ", msg.strerror)
    exit(-1)

print(clientSocket.recv(1024).decode('ascii'))

number = round(random.uniform(10, 100), 4)

print(f"My number {number}")

number = struct.pack("!f", number)

clientSocket.send(number)

print(clientSocket.recv(1024).decode('ascii'))

clientSocket.close()

