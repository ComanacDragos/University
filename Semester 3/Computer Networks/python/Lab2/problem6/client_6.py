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
import sys
import random
import time


def worker():
    left = 1
    right = 1000

    try:
        clientSocket = socket.create_connection((sys.argv[1], int(sys.argv[2])))
    except socket.error as msg:
        print(msg.strerror)

    while True:
        nr = random.randint(left, right)

        try:
            clientSocket.sendall(struct.pack('!I', nr))
            response = clientSocket.recv(1024).decode('ascii')
            print(f'Sent {nr}, received {response}')

            if response == 'smaller':
                left = nr
            elif response == 'larger':
                right = nr
            else:
                break
        except socket.error as msg:
            print(msg.strerror)
            exit(1)
        time.sleep(0.25)
    clientSocket.close()


worker()
