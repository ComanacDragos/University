#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>

#include <WinSock2.h>
#include <wsipv6ok.h>

#pragma comment(lib, "Ws2_32.lib")
#include <stdlib.h>

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
		printf("Error on server socket\n");
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
		c = accept(s, (struct sockaddr*) & client, &l);

		err = WSAGetLastError();

		if (c < 0) {
			printf("Accept error: %d\n", err);
			continue;
		}

		printf("Incoming client from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		char ch;
		int res = recv(c, &ch, sizeof(char), 0);

		if (res != sizeof(char))
			printf("Error on receiving char\n");
		else
			printf("Received %c\n", ch);

		int len;
		res = recv(c, (char*)&len, sizeof(len), 0);
		len = ntohl(len);

		if (res != sizeof(len))
			printf("Error on receiving len\n");
		else
			printf("Received %d\n", len);

		char* string = (char*)malloc(sizeof(char) * len);
		if (string == nullptr) {
			printf("Error on malloc\n");
			continue;
		}
		res = recv(c, string, sizeof(char) * len, 0);

		if (res != sizeof(char) * len)
			printf("Error on receiving string\n");
		else
			printf("Received %s\n", string);

		len = 0;

		int* arr = (int*)malloc(sizeof(int) * strlen(string));

		for (int i = 0; i < strlen(string); i += 1)
			if (string[i] == ch)
				arr[len++] = htonl(i);

		len = htonl(len);
		res = send(c, (char*)&len, sizeof(len), 0);

		if (res != sizeof(len))
			printf("Error on sending len\n");

		for (int i = 0; i < ntohl(len); i += 1) {
			res = send(c, (char*)&arr[i], sizeof(arr[i]), 0);

			if (res != sizeof(arr[i]))
				printf("Error on sending position\n");
		}

		free(string);
		free(arr);
		closesocket(c);
	}

	WSACleanup();
}