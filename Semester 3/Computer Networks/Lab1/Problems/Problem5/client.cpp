#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<cstdint>
#include<wsipv6ok.h>
#pragma comment(lib,"Ws2_32.lib")

#include <stdio.h>
#include <string.h>

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets Library");
        return -1;
    }

    int c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("Error on client socket\n");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.0.157");

    int nr;
    printf("nr: ");
    scanf("%d", &nr);

    if (connect(c, (struct sockaddr*) & server, sizeof(server)) < 0) {
        printf("Error on connecting to server\n");
        return 1;
    }

    nr = htonl(nr);
    send(c, (char*)&nr, sizeof(nr), 0);
    
    int len;

    int res = recv(c, (char*)&len, sizeof(len), 0);

    if (res != sizeof(len))
        printf("Error on len\n");

    len = ntohl(len);
    printf("Received %d\n", len);

    printf("The divisors are:\n");

    for (int i = 0; i < len; i += 1) {
        int aux;
        res = recv(c, (char*)&aux, sizeof(aux), 0);
        if (res != sizeof(aux))
            printf("Error on receiving number\n");
        printf("%d\n", ntohl(aux));
    }
    closesocket(c);
    return 0;
}