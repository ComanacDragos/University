"""
The teacher is the “server”; using select and TCP communication it waits for questions from the group leaders.
The group leaders know the IP and the port that the teacher listens on.

When a question is received, the sever generates the response (a string and an array of integers – the string and
the values in this array should be randomly generated) and sends back the response to the group leader.

Create at least 3 groups with minimum 5 students each
"""

import socket
import struct
import threading

import string
import random

teacherAddress = ("192.168.0.101", 4444)

def worker(leaderSocket):
    print(f"Connected leader: {leaderSocket.getpeername()}")

    while True:
        try:
            responseLen = struct.unpack("!I", leaderSocket.recv(4))[0]
            response = leaderSocket.recv(responseLen).decode('ascii')

            strLen = random.randint(5, 10)

            randomString = ""

            for i in range(strLen):
                randomString += random.choice(string.ascii_lowercase)

            responseString = f"Answer from teacher: {strLen} {randomString} to {response}"

            print(f"Sending {responseString} to {leaderSocket.getpeername()}")

            leaderSocket.sendall(struct.pack("!I", len(responseString)))
            leaderSocket.sendall(bytes(responseString, 'ascii'))

            intLen = random.randint(5, 10)

            leaderSocket.sendall(struct.pack("!I", intLen))
            print(f"Sent {intLen} to {leaderSocket.getpeername()}")

            for i in range(intLen):
                myInt = random.randint(1, 10)
                leaderSocket.sendall(struct.pack("!I", myInt))
                print(f"Sent {myInt} to {leaderSocket.getpeername()}")


        except socket.error as msg:
            print(msg.strerror)
        except struct.error:
            print(f"{leaderSocket.getpeername()} disconnected")
            break


def main():
    try:
        teacherSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        teacherSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        teacherSocket.bind(teacherAddress)
        teacherSocket.listen(5)
    except socket.error as msg:
        print(msg.strerror)

    print('Listening...')
    while True:
        try:
            leaderSocket, leaderAddress = teacherSocket.accept()

            threading.Thread(target=worker, args=(leaderSocket,)).start()
        except socket.error as msg:
            print("Accept error:", msg.strerror)
main()