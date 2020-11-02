"""
Un client trimite unui server un nume de calculator sub forma unui sir de caractere de lungime cel mult 100.
Serverul va returna clientului un numar reprezentat pe 4 octeti fara semn ce reprezinta adresa IP a calculatorului respectiv.
Clientul va afisa corespunzator adresa IP (in format zecimal cu “.”)
sau un mesaj de eroare daca numele calculatorului nu poate fi translatat intr-o adresa IP.
"""

import socket
import sys
import struct

serverAddress = ('192.168.0.115', 1234)
clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

print(socket.gethostbyaddr('192.168.0.115'))

host = 'DESKTOP-E94DLUNa'

clientSocket.sendto(bytes(host, 'ascii'), serverAddress)

response, addr = clientSocket.recvfrom(4)

response = socket.inet_ntoa(response)
print(response)