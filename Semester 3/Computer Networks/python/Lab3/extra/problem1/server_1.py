"""
Un client trimite unui server o cerere prin care ii cere acestuia data si ora curenta.
Serverul va returna clientului data sub forma unui intreg ce reprezinta numarul de secunde trecute de la 1 ianuarie 1970.
Clientul va afisa corespunzator data pe baza acestui intreg.
"""
import time
import socket
import struct
import sys

try:
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverSocket.bind((sys.argv[1], int(sys.argv[2])))
except socket.error as msg:
    print(msg.strerror)
    exit(1)
except Exception as msg:
    print(msg)
    exit(1)

while True:
    try:
        len = struct.unpack('!I', serverSocket.recvfrom(4)[0])[0]
        message, address = serverSocket.recvfrom(len)
        if message.decode('ascii') == 'Da-mi date!\0':
            print(f"Incoming connexion {address}")
            serverSocket.sendto(struct.pack('!d', time.time()), address)
        else:
            print(f"Malformed data from {address}, {message.decode('ascii')}")

    except socket.error as msg:
        print(msg.strerror)

