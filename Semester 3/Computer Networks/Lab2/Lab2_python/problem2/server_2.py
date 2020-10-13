import socket
import struct
import os

def process_requirement(s):
    output_len = s.recv(4)
    output_len = struct.unpack("!I", output_len)[0]
    print("Received: " + str(output_len), type(output_len))

    path = s.recv(output_len).decode(encoding="ascii")

    print("Received: " + path + " len: " + str(len(path)))

    try:
        f = open(path)

        content = ""

        for line in f.readlines():
            content += line

        s.send(struct.pack("!i", len(content)))
        s.send(content.encode('ascii'))
    except FileNotFoundError:
        s.send(struct.pack("!i", -1))

    s.close()


def main():
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.bind(('192.168.0.157', 1235))
    s.listen(5)

    print("Waiting for connections")
    while True:
        client_socket, client_address = s.accept()
        print("Incoming from : " + client_address[0] + ":" + str(client_address[1]))

        if os.fork() == 0:
            process_requirement(client_socket)


main()