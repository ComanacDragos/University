#include <stdio.h>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<WinSock2.h>
#include<cstdint>
#include<wsipv6ok.h>
#pragma comment(lib,"Ws2_32.lib")
#include <string.h>

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets Library");
        return -1;
    }

    int c = socket(AF_INET, SOCK_STREAM, 0);

    if (c < 0) {
        printf("Error on client socket");
        return 1;
    }

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));

    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.0.157");

    char s[254];
    fgets(s, 254, stdin);
    s[strlen(s) - 1] = NULL;
    
    if (connect(c, (struct  sockaddr*) & server, sizeof(server)) < 0) {
        printf("Error on connecting to server\n");
        return 1;
    }

    int len = htons(strlen(s));
    printf("Converted len: %d\n", len);

    send(c, (char*)&len, sizeof(len), 0);

    len = strlen(s);

    send(c, s, sizeof(char) * len, 0);

    recv(c, s, sizeof(char) * len, 0);

    printf("Reversed: %s\n", s);

    WSACleanup();
    closesocket(c);

    return 0;
}
