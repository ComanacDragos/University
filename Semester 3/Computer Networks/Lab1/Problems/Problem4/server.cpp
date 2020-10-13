#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <stdio.h>

#include <WinSock2.h>
#include <cstdint>
#include <wsipv6ok.h>

#pragma comment(lib, "Ws2_32.lib")

int main()
{
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
		printf("Error on server socket");
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

	printf("Listening for incoming connections:\n");
	while (1) {
		c = accept(s, (struct sockaddr*) & client, &l);
		err = WSAGetLastError();

		if (c < 0) {
			printf("Accept error: %d", err);
			continue;
		}
		printf("Incoming connected client from: %s:%d\n",
			inet_ntoa(client.sin_addr), ntohs(client.sin_port));

		int len;
		char *s1, *s2, *s3;

		int res = recv(c, (char*)&len, sizeof(len), 0);

		if (res != sizeof(int))
			printf("Error on len1\n");

		len = ntohl(len);
		printf("Received len1: %d\n", len);
		s1 = (char*)malloc(sizeof(char) * len);

		res = recv(c, s1, len, 0);

		if (res != len)
			printf("Error on s1\n");

		res = recv(c, (char*)&len, sizeof(len), 0);

		if (res != sizeof(int))
			printf("Error on len2\n");

		len = ntohl(len);
		printf("Received len2: %d\n", len);
		s2 = (char*)malloc(sizeof(char) * len);

		res = recv(c, s2, len, 0);

		if (res != len)
			printf("Error on s2\n");

		printf("Received s1: %s, s2: %s\n", s1, s2);

		s3 = (char*)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));

		int i = 0, j = 0, k = 0;

		while(i<strlen(s1) && j<strlen(s2))
			if (s1[i] < s2[j]) {
				s3[k++] = s1[i];
				i += 1;
			}
			else {
				s3[k++] = s2[j];
				j += 1;
			}

		while (i < strlen(s1))
		{
			s3[k++] = s1[i];
			i += 1;
		}
		while (j < strlen(s2))
		{
			s3[k++] = s2[j];
			j += 1;
		}
		s3[k] = NULL;
		printf("Sending: %s\n", s3);
		send(c, s3, sizeof(char) * (strlen(s3)+1), 0);

		free(s1);
		free(s2);
		free(s3);

		closesocket(c);
	}

	WSACleanup();
}
