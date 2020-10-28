import sys
import socket
import multiprocessing


def worker(message, address):
    print("Received from: " + str(address) + " " + message.decode('ascii'))

    responseSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    responseSocket.sendto(message, address)

    exit(0)


def main():
    address = (sys.argv[1], int(sys.argv[2]))

    try:
        serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        serverSocket.bind(address)
    except socket.error as msg:
        print(msg.strerror)
        exit(1)

    print("Listening...")
    while True:
        message, addressFrom = serverSocket.recvfrom(1024)

        multiprocessing.Process(target=worker, args=(message, addressFrom)).start()


if __name__ == '__main__':
    main()
