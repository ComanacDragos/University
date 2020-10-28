import socket
import struct

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

s.connect(('192.168.0.157', 1235))

command = input("Give command: ")

s.send(struct.pack("!I", len(command)))

s.send(bytes(command, encoding="ascii"))

output_len = struct.unpack("!i", s.recv(4))[0]

if output_len != -1:
    print(f"Received: {output_len}")
    output = s.recv(output_len).decode('ascii')
    print("Received:")
    print(output)

    name = command.split("/")[-1]
    name += "-copy"

    f = open(name, "w")
    f.write(output)
else:
    print("Invalid path")
