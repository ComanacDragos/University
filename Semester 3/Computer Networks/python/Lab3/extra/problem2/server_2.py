"""
Un client trimite unui server un nume de calculator sub forma unui sir de caractere de lungime cel mult 100.
Serverul va returna clientului un numar reprezentat pe 4 octeti fara semn ce reprezinta adresa IP a calculatorului respectiv.
Clientul va afisa corespunzator adresa IP (in format zecimal cu “.”)
sau un mesaj de eroare daca numele calculatorului nu poate fi translatat intr-o adresa IP.
"""

import socket
import sys
import struct

serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
serverSocket.bind(('192.168.0.115', 1234))

print('Listening...')
while True:
    host, address = serverSocket.recvfrom(100)

    response = struct.pack('!I', 0)
    try:
        host = socket.gethostbyname(host.decode('ascii'))
        response = socket.inet_aton(host)
    except socket.error as msg:
        print(msg.strerror)

    serverSocket.sendto(response, address)
