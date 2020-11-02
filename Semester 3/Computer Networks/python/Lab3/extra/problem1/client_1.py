"""
Un client trimite unui server o cerere prin care ii cere acestuia data si ora curenta.
Serverul va returna clientului data sub forma unui intreg ce reprezinta numarul de secunde trecute de la 1 ianuarie 1970.
Clientul va afisa corespunzator data pe baza acestui intreg.
"""
import time
import socket
import struct
import sys
import datetime

try:
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    serverAddress = (sys.argv[1], int(sys.argv[2]))
except socket.error as msg:
    print(msg.strerror)
    exit(1)
except Exception as msg:
    print(msg)
    exit(1)

while True:
    try:
        clientSocket.sendto(struct.pack('!I', 12), serverAddress)
        clientSocket.sendto(bytes('Da-mi date!\0', 'ascii'), serverAddress)

        print(time.time())
        response, address = clientSocket.recvfrom(8)

        if address != serverAddress:
            continue

        response = struct.unpack('!d', response)[0]

        print(response, time.ctime(response))

        if address == serverAddress:
            break
    except socket.error as msg:
        print(msg.strerror)

clientSocket.close()