#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>

#include <WinSock2.h>
#include <wsipv6ok.h>

#pragma comment(lib, "Ws2_32.lib")

int main() {
	SOCKET s;
	struct sockaddr_in server, client;
	int c, l, err;

	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
		printf("Error initializing windows sockets library");
		return -1;
	}

	s = socket(AF_INET, SOCK_STREAM, 0);

	if (s < 0) {
		printf("Error on server socket\n");
		return 1;
	}

	memset(&server, 0, sizeof(server));
	server.sin_port = htons(1234);
	server.sin_family = AF_INET;

	server.sin_addr.s_addr = INADDR_ANY;

	if (bind(s, (struct sockaddr*) & server, sizeof(server)) < 0) {
		perror("Bind error: ");
		return 1;
	}

	listen(s, 5);

	l = sizeof(client);

	memset(&client, 0, sizeof(client));

	printf("Listening for incoming connections\n");
	while (1) {
		c = accept(s, (struct sockaddr*) & client, (int*)&l);
		
		err = errno;

		err = WSAGetLastError();

		if (c < 0) {
			printf("accept error: %d", err);
			continue;
		}

		printf("Incoming connected client from: %s:%d\n",
			inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		int len;

		int res = recv(c, (char*)&len, sizeof(len), 0);

		if (res != sizeof(len))
			printf("Error receiving length");

		len = ntohs(len);

		char* s = (char*)malloc(sizeof(char) * len);

		if (s == NULL) {
			printf("Error on malloc");
			return 1;
		}

		res = recv(c, s, sizeof(char) * len, 0);

		if (res != sizeof(char) * len)
			printf("Error on receiving string\n");

		s[len - 1] = NULL;
		len -= 1;

		printf("Received string: %s of size %d", s, len);
		int count = 0;
		for (int i = 0; i < len; i += 1){
			if (s[i] == ' ')
				count += 1;
		}
		count = htons(count);

		res = send(c, (char*)&count, sizeof(count), 0);

		closesocket(c);
	}
	WSACleanup();
}