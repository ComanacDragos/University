"""
The server chooses a random integer number. Each client generates a random integer number and send it to the server.
The server answers with the message “larger” if the client has sent a smaller number than the server’s choice,
or with message “smaller” if the client has send a larger number than the server’s choice.
Each client continues generating a different random number (larger or smaller than the previous) according to the server’s indication.
When a client guesses the server choice – the server sends back to the winner the message “You win – within x tries”.
It also sends back to all other clients the message “You lost – after y retries!” (x and y are the number of tries of each respective client).
The server closes all connections upon a win and it chooses a different random integer for the next game (set of clients)
"""

import socket
import struct
import threading
import time
import random

left = 1
right = 1000

SRN = random.randint(left, right)
print(f"My number is {SRN}")

threads = []
winner = None
myLock = threading.Lock()
reset = threading.Event()
reset.clear()


def worker(clientSocket):
    global SRN, myLock, reset, winner
    print(f"Client connected from {clientSocket.getpeername()}")

    guesses = 0

    while winner is None:
        try:
            nr = struct.unpack('!I', clientSocket.recv(4))[0]

            guesses += 1

            if nr < SRN:
                clientSocket.sendall(bytes('smaller', 'ascii'), 0)
            elif nr > SRN:
                clientSocket.sendall(bytes('larger', 'ascii'), 0)
            else:
                myLock.acquire()
                if winner is None:
                    winner = clientSocket.getpeername()
                myLock.release()
        except socket.error as msg:
            print(msg.strerror)
            exit(1)

    try:
        if winner == clientSocket.getpeername():
            clientSocket.sendall(bytes(f" You win with {guesses} guesses", 'ascii'))
            reset.set()
        else:
            clientSocket.sendall(bytes(f" You lost with {guesses} guesses", 'ascii'))

        time.sleep(1)
        clientSocket.close()
    except socket.error as msg:
        print(msg.strerror)


def resetServer():
    global reset, threads, winner, SRN, left, right
    while True:
        reset.wait()

        print('Joining')
        for t in threads:
            t.join()

        SRN = random.randint(left, right)
        winner = None
        threads = []
        reset.clear()

        print('Game over. New number:', SRN)


def main():
    try:
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        serverSocket.bind(('192.168.0.115', 1234))
        serverSocket.listen(10)
    except socket.error as msg:
        print(msg.strerror)
        exit(1)

    threading.Thread(target=resetServer, daemon=True).start()

    print('Listening...')
    while True:
        try:
            clientSocket , _ = serverSocket.accept()

            t = threading.Thread(target=worker, args=(clientSocket,))
            t.start()

            threads.append(t)
        except socket.error as msg:
            print(msg.strerror)


if __name__ == '__main__':
    main()