#include <stdio.h>
#include <iostream>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
// on Windows include and link these things
#include<WinSock2.h>
// for uint16_t
#include<cstdint>
// for inet_ntoa
#include<wsipv6ok.h>
// this is how we can link a library directly from the source code with the VC++ compiler –
// otherwise got o project settings and link to it explicitly
#pragma comment(lib,"Ws2_32.lib")

#include <string.h>

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets Library");
        return -1;
    }
    int len, sum, aux;
    printf("len = ");
    scanf("%d", &len);

    int* v = (int*)malloc(sizeof(int) * len);

    for (int i = 0; i < len; i += 1)
        scanf("%d", v + i);

    int c;

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("Error on client socket\n");
        return 1;
    }

    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));

    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.0.157");

    if (connect(c, (struct sockaddr*) & server, sizeof(server)) < 0) {
        printf("Eroare la conectarea la server");
        return 1;
    }

    aux = len;
    aux = htons(aux);

    send(c, (char*)&aux, sizeof(aux), 0);

    for (int i = 0; i < len; i += 1) {
        v[i] = htons(v[i]);
    
        send(c, (char*)&v[i], sizeof(v[i]), 0);
    }

    recv(c, (char*)&sum, sizeof(sum), 0);

    sum = ntohs(sum);

    printf("Suma este %d\n", sum);

    WSACleanup();
    closesocket(c);
}
