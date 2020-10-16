"""
The server chooses a random float number <SRF>.
Run multiple clients. Each client chooses a random float number <CRF> and send it to the server.
When the server does not receive any incoming connection for at least 10 seconds it chooses the client that has guessed
the best approximation (is closest) for its own number and sends it back the message “You have the best guess with an
error of <SRV>-<CRF>”. It also sends to each other client the string “You lost !”.
The server closes all connections after this.
"""
import socket
import struct
import random
import threading
import sys
import time

random.seed()
SRF = round(random.uniform(10, 100), 4)
print('Server number:', SRF)
myLock = threading.Lock()

threads = []
clientCount = 0
error = 2**32-1
winningThread = -1
endGameEvent = threading.Event()
endGameEvent.clear()

def worker(clientSocket, count):
    global error, winningThread, SRF, threads, clientCount, error

    print('Connected: ', count, clientSocket.getpeername())

    message = "Welcome to the game. You are number: " + str(count)
    clientSocket.sendall(bytes(message, 'ascii'))

    clientNumber = clientSocket.recv(4)

    clientNumber = round(struct.unpack("!f", clientNumber)[0],4)

    print(f"Received {clientNumber} from {count}")

    localError = abs(SRF - clientNumber)

    myLock.acquire()
    if localError < error:
        error = localError
        winningThread = count
    myLock.release()

    endGameEvent.wait()

    if count == winningThread:
        clientSocket.sendall(bytes(f"You won with the error: {round(error, 4)}", 'ascii'))
    else:
        clientSocket.sendall(bytes("You lost", 'ascii'))

    clientSocket.close()

def closeSrv():
    global threads, endGameEvent

    endGameEvent.set()
    for thread in threads:
        thread.join()


def main():
    global SRF, threads, clientCount

    try:
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.settimeout(10)
        serverSocket.bind(('localhost', 1234))
        serverSocket.listen(5)
    except socket.error as msg:
        print(msg.strerror)
        exit(-1)

    print("Waiting for connections...")
    threadCount = []
    while True:
        try:
            clientSocket, clientAddr = serverSocket.accept()

            threadCount.append(len(threadCount))
            t = threading.Thread(target=worker, args=(clientSocket, threadCount[len(threadCount) - 1]))
            threads.append(t)

            t.start()
        except socket.timeout:
            closeSrv()
            break
main()
