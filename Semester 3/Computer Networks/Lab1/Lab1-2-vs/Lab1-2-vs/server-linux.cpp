#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
// for inet_ntoa
#include <arpa/inet.h>
// for close
#include <unistd.h>
#define closesocket close
typedef int SOCKET;

int main(){
    SOCKET s;
    struct sockaddr_in server, client;
    int c, l, err;

    s = socket(AF_INET, SOCK_STREAM, 0);

    if(s<0){
        printf("Error on creating server socket\n");
    }

    memset(&server, 0, sizeof(server));

    server.sin_port = htons(1234);
    server.sin_family = AF_INET;

    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, (struct sockaddr*)& server, sizeof(server)) < 0){
        perror("Bind error:");
        return 1;
    }
    listen(s, 5);


    l = sizeof(client);
    memset(&client, 0, sizeof(client));
    printf("Starting...Waiting for clients\n");
    while(1){

        c = accept(s, (struct sockaddr*)&client, (socklen_t*)&l);

        err = errno;

        if(c<0){
            printf("accept error: %d", err);
            continue;
        }

        printf("Incoming connected client from: %s:%d\n",
            inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        int len, sum = 0,  current;
        int res = recv(c, (char*)&len, sizeof(len), 0);

        if(res != sizeof(len))
            printf("Error receiving operand\n");

        len = ntohs(len);

        for(int i=0;i<len;i+=1){
            res = recv(c, (char*)&current, sizeof(current), 0);

            if(res != sizeof(current))
                printf("Error receiving number\n");

            sum += current;
        }

        res = send(c, (char*)&sum, sizeof(sum), 0);

        if(res != sizeof(sum))
        printf("Error sending result\n");

        closesocket(c);
    }
}
