#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <wsipv6ok.h>
#include <thread>
#include <mutex>

#pragma comment(lib, "Ws2_32.lib")

float myFloat = (float)(rand() % 1000) / (float)(rand() % 100);
std::mutex mtx;

void worker(int clientSocket) {
	closesocket(clientSocket);
}

int main() {
	SOCKET s;
	struct sockaddr_in server, client;
	int c, l, err;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
		printf("Error initializing the Windows Sockets LIbrary");
		return -1;
	}

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s < 0) {
		printf("Error on creating socket");
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(4321);
	server.sin_family = AF_INET;

}