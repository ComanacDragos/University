import socket
import sys
import select
import struct

serverAddress = ("192.168.0.101", 7000)

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
peers = {}

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
                clientSocket, fromAddress = serverSocket.accept()
                clientSocket.sendall(bytes("Welcome!", 'ascii'))
                response = clientSocket.recv(32).decode('ascii')
                response = response.split('|')
                tokens = response[1][1:-1].replace(' ', '').replace('\'', '').split(',')
                udpAddress = (tokens[0], int(tokens[1]))
                nickname = response[0]
                print(f"Incoming connection from {fromAddress[0]}:{fromAddress[1]}, nickname: {nickname}")

                clientSocket.sendall(struct.pack('!I', len(peers)))
                for peer in peers.keys():
                    message = f"{peers[peer][1]}|{peers[peer][0]}"
                    clientSocket.sendall(struct.pack('!I', len(message)))
                    clientSocket.sendall(bytes(message, 'ascii'))
                print(f"Done sending to {response}")
                toBeRemoved = []
                for client in master[1:]:
                    try:
                        client.sendall(bytes(f"{udpAddress}|{nickname}", 'ascii'))
                    except socket.error as msg:
                        print(msg.strerror)
                        toBeRemoved.append(client)
                #perhaps remove

                master.append(clientSocket)
                peers[fromAddress] = [nickname, udpAddress]
                print(peers, len(master))
            except socket.error as msg:
                print(msg.strerror)
        else:
            message = ""
            try:
                response = sock.recv(1024).decode('ascii')

                if response == 'QUIT' or response == '':
                    message = f"{peers[sock.getpeername()][1]}|QUIT"
                    if response == '':
                        message += ' ABRUPTLY'
                    master.remove(sock)
                    del peers[sock.getpeername()]
                    sock.close()
            except socket.error as msg:
                print(msg.strerror)
                message = f"{peers[sock.getpeername()][1]}|QUIT ABRUPTLY"
                master.remove(sock)
                del peers[sock.getpeername()]
                sock.close()

            toBeRemoved = []
            for client in master[1:]:
                try:
                    client.sendall(bytes(message, 'ascii'))
                except socket.error as msg:
                    print(msg.strerror)
                    toBeRemoved.append(client)


