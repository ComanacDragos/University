"""
Students

Each “student” will read from the command line a port number group_port and an integer that states
if the student is the group leader (1) or not (0).

The group leader periodically (from 5 to 5 seconds) sends the message “leader”
the port group_port using broadcast to notify the students that he/she is the group leader.

The other students will send their questions (a string), randomly from 3 to 3 seconds to the group
leader (i.e. from 3 to 3 seconds, generate a random number between 0 and 1; if it is larger than 0.5 compose
a random string and send it; otherwise do nothing). You can choose if you want to use TCP or UDP for this.

The group leader will “forward” these questions to the teacher using TCP.
When the teacher responds, the group leader will send the original question and the teacher’s response on the port
group_port using broadcast.
"""

import sys
import socket
import struct
import threading
import time
import random
import select

broadcastLock = threading.Lock()

try:
    ipAddress = "192.168.0.101"
    port = int(sys.argv[1])
    groupPort = int(sys.argv[2])
    isLeader = int(sys.argv[3])

except Exception as msg:
    print(msg)
    sys.exit(1)


def leader_broadcast_thread(broadCastSocket):
    while True:
        try:
            broadcastLock.acquire()
            broadCastSocket.sendto(b'leader', ("<broadcast>", groupPort))
            broadcastLock.release()
            #print('Sent leader')
        except socket.error as msg:
            print(msg.strerror)
        time.sleep(5)


def leader_handle():
    teacherAddress = ("192.168.0.101", 4444)
    try:
        broadcastSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        broadcastSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        broadcastSocket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)

        broadcastSocket.bind((ipAddress, port))

    except socket.error as msg:
        print(msg.strerror)

    threading.Thread(target=leader_broadcast_thread, args=(broadcastSocket,)).start()

    try:
        teacherSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        teacherSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        print('Connecting...')
        teacherSocket.connect(teacherAddress)
    except socket.error as msg:
        print(msg.strerror)

    master = [teacherSocket, broadcastSocket]
    print("Starts leader...")
    while True:
        try:
            ready, _, _ = select.select(master, [], [])
        except select.error as msg:
            print(msg)

        for sock in ready:
            if sock == teacherSocket:
                try:
                    responseLen = struct.unpack("!I", teacherSocket.recv(4))[0]
                    response = teacherSocket.recv(responseLen).decode('ascii')

                    intlen = struct.unpack("!I", teacherSocket.recv(4))[0]

                    for i in range(intlen):
                        myInt = struct.unpack("!I", teacherSocket.recv(4))[0]
                        response += f" {myInt}"

                    broadcastLock.acquire()
                    broadcastSocket.sendto(bytes(response, 'ascii'), ("<broadcast>", groupPort))
                    broadcastLock.release()
                    print(f"Sent response from teacher {response}")

                except socket.error as msg:
                    print(msg.strerror)
            elif sock == broadcastSocket:
                try:
                    response, fromAddress = broadcastSocket.recvfrom(64)

                    teacherSocket.send(struct.pack("!I", len(response.decode())))
                    teacherSocket.send(response)
                    print(f"Sent to teacher: {response.decode('ascii')}")

                except socket.error as msg:
                    print(msg.strerror)


def student_thread(leaderAddress):
    try:
        questionSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        questionSocket.bind((ipAddress, port))
    except socket.error as msg:
        print(msg.strerror)

    while True:
        if random.randint(1, 2) == 1:
            questionSocket.sendto(bytes(f"question from {ipAddress}:{port}", 'ascii'), leaderAddress)
            print(f'Sent question to leader {leaderAddress}')
        time.sleep(3)


def student_handle():
    try:
        broadcastSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        broadcastSocket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        broadcastSocket.bind(("", groupPort))
    except socket.error as msg:
        print(msg.strerror)

    leader = None

    print('Listening for leader...')
    while leader is None:
        try:
            response, fromAddress = broadcastSocket.recvfrom(128)
            print(response.decode('ascii'))
            if response.decode('ascii') == 'leader':
                leader = fromAddress
        except socket.error as msg:
            print(msg.strerror)
    print(f'Leader is {leader}')

    threading.Thread(target=student_thread, args=(leader,)).start()

    print('Start listening for answers')
    while True:
        try:
            response, fromAddress = broadcastSocket.recvfrom(128)
            if response.decode('ascii') != 'leader':
                if fromAddress == leader:
                    print(f"Received {response.decode('ascii')}")
                else:
                    print("Received from another", response.decode('ascii'), fromAddress)
        except socket.error as msg:
            print(msg.strerror)

def main():
    if isLeader == 0:
        student_handle()
    else:

        leader_handle()
main()