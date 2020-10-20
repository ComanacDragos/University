#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <wsipv6ok.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")


int main(int argc, char** argv) {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {
        printf("Error initializing the Windows Sockets Library");
        return -1;
    }
    
    SOCKET c;
    struct sockaddr_in server;

    if (argc != 5) {
        printf("bad arguments, required %d\n", argc);
        exit(1);
    }

    c = socket(AF_INET, SOCK_STREAM, 0);
    if (c < 0) {
        printf("Eroare la socket!\n");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.0.101");

    int n = atoi(argv[3]), port = atoi(argv[4]), nrDiv;

    if (connect(c, (struct sockaddr*) & server, sizeof(server)) < 0) {
        perror("Eroare la conectare!: ");
        return 1;
    }

    n = htonl(n);
    port = htonl(port);

    int rez = send(c, (char*)&n, sizeof(int), 0);
    if (rez != sizeof(int))
        printf("Eroare la send!\n");
    rez = send(c, (char*)&port, sizeof(int), 0);
    if (rez != sizeof(int))
        printf("Eroare la send!\n");

    //server nou
    
    int s1, c1;
        struct sockaddr_in server1, client1;
        s1 = socket(AF_INET, SOCK_STREAM, 0);

        if(s1<0){
                printf("Eroare la socket!\n");
                return 1;
        }
    port=atoi(argv[4]);
    printf("port: %d\n", port);

    memset(&server1, 0, sizeof(server1));
        server1.sin_port = port;
        server1.sin_family = AF_INET;
        server1.sin_addr.s_addr = INADDR_ANY;

        if(bind(s1, (struct sockaddr *) &server1, sizeof(server1)) < 0){
                printf("Eroare la bind!\n");
                return 1;
        }

        listen(s1, 1);

        int l = sizeof(client1);
        memset(&client1, 0, sizeof(client1));

    int ok = 1;
    ok = htonl(ok);
    send(c, (char*)&ok, sizeof(int), 0);
    closesocket(c);
    printf("accepting");
    c1= accept(s1, (struct sockaddr *) &client1, &l);
        if(c1 < 0)
              printf("Eroare la accept!\n");
        printf("connected");
    //server

    rez = recv(c1, (char*)&nrDiv, sizeof(int), 0);
    if (rez != sizeof(int))
        printf("Eroare la recv!\n");

    nrDiv = ntohl(nrDiv);
    printf("Numarul de divizori este: %d\n", nrDiv);

    closesocket(c1);
}
