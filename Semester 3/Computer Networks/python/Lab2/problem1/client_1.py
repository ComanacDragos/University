import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(("192.168.0.157", 1234))

command = input("Give command: ")

res = s.send(struct.pack("!I", len(command) + 1))

if res != 4:
    print("Error on sending length")

res = s.send(bytes(command + '\0', encoding='utf8'))

if res != len(command) + 1:
    print("Error on sending string")

output_len = s.recv(4)
output_len = struct.unpack('!I', output_len)[0]
print("Received: " + str(output_len))

output = s.recv(output_len).decode()[:-2]
print("Received:")
print(output)
print("End.")


