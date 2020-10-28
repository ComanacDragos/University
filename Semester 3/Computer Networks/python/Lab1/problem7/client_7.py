"""
The client sends to the server a string and two numbers (s, I, l).
 The sever returns to the client the substring of s starting at index I, of length l.
"""
import socket
import struct

try:
    clientSocket = socket.create_connection(('192.168.0.101', 1234))
except socket.error as msg:
    print('Error ', msg.strerror)
    exit(1)

try:
    print(clientSocket.recv(1024).decode('ascii'))

    string = input('Give string: ')
    start = int(input('Give start: '))
    length = int(input('Give length: '))

    clientSocket.sendall(struct.pack('!I', len(string)))
    clientSocket.sendall(bytes(string, 'ascii'))
    clientSocket.sendall(struct.pack('!i', start))
    clientSocket.sendall(struct.pack('!i', length))

    length = struct.unpack('!i', clientSocket.recv(4))[0]
    if length == -1:
        print('Bad start and length')
    else:
        print('Received: ', clientSocket.recv(1024).decode('ascii'))
except socket.error as msg:
    print('Error ', msg.strerror)