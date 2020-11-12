import socket
import sys
import select
import struct
import random

serverAddress = ("192.168.0.101", 7000)
myAddress = ("192.168.0.101", 1234 + random.randint(1, 60000))

nickname = input(">>")
serverSocket = None
udpSocket = None

peers = {}
try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    serverSocket.connect(serverAddress)

    response = serverSocket.recv(1024)
    print(response.decode('ascii'))
    serverSocket.sendall(bytes(f"{nickname}|{myAddress}", 'ascii'))

    length = struct.unpack('!I', serverSocket.recv(4))[0]
    #print(length)
    for i in range(length):
        length = struct.unpack('!I', serverSocket.recv(4))[0]
        response = serverSocket.recv(length)
        response = response.decode('ascii').split('|')
        tokens = response[0][1:-1].replace(' ', '').replace('\'', '').split(',')
        newAddress = (tokens[0], int(tokens[1]))
        #print(tokens, response[1])
        peers[newAddress] = response[1]

    #print("Current peers: ")
    #print(peers)

    udpSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udpSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

    udpSocket.bind(myAddress)
except socket.error as msg:
    print(msg)
    exit(1)

master = [sys.stdin, serverSocket, udpSocket]

while True:
    try:
        ready, _, _ = select.select(master, [], [])
    except socket.error as msg:
        print(msg.strerror)
        continue

    for sock in ready:
        if sock == serverSocket:
            try:
                response = serverSocket.recv(128)
                response = response.decode('ascii').split('|')
                tokens = response[0][1:-1].replace(' ', '').replace('\'', '').split(',')

                newAddress = (tokens[0], int(tokens[1]))
                if response[1] == 'QUIT':
                    print(f"<server> {peers[newAddress]} has quit")
                    del peers[newAddress]
                elif response[1] == 'QUIT ABRUPTLY':
                    print(f"<server> {peers[newAddress]} has quit abruptly")
                    del peers[newAddress]
                else:
                    peers[newAddress] = response[1]
                    print(f"<server> {peers[newAddress]} has connected")
            except socket.error as msg:
                print(msg.strerror)
        elif sock == udpSocket:
            response, fromAddress = udpSocket.recvfrom(1024)

            if fromAddress not in peers.keys():
                print(f"Received bad data {response.decode}")
            else:
                print(f"<{peers[fromAddress]}> {response.decode('ascii')}")
        else:
            message = input()

            if message == 'QUIT':
                serverSocket.sendall(bytes('QUIT', 'ascii'))
                serverSocket.close()
                udpSocket.close()
                exit(0)

            for peer in peers.keys():
                udpSocket.sendto(bytes(message, 'ascii'), peer)
                #print(f"Sent {message} to {peer}")
serverSocket.close()
