/*#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int s = socket(AF_INET, SOCK_STREAM, 0), c, l, err;

    if(s<0){
        printf("Error on server socket\n");
        return 1;
    }

    struct sockaddr_in server, client;

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, (struct sockaddr*)&server, sizeof(server)) < 0){
       perror("Bind error:");
       return 1;
    }

    listen(s, 5);
    l = sizeof(client);
    memset(&client, 0, sizeof(client));

    printf("Listening for incoming connections\n");

    while(1){
        char *reversed;

        c = accept(s, (struct sockaddr*) & client, (socklen_t*)&l);

        err = errno;

        if(c<0){
            printf("Accept error: %d\n", err);
            continue;
        }

        printf("Incoming connected client from: %s:$d\n",
                inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        int len;
        int res = recv(c, (char*)&len, sizeof(len), 0);

        if(res!=sizeof(int))
            printf("Error on length\n");

        len = ntohs(len);

        printf("Received length: %d\n", len);

        reversed = (char*)malloc(sizeof(char) * (len+1));

        res = recv(c, reversed, sizeof(char) * len, 0);

        if(res != sizeof(char) * len)
            printf("Error on receiving");

        printf("Received array: %s\n", reversed);

        for(int i=0;i<len/2;i+=1){
            char aux = reversed[i];
            reversed[i] = reversed[len-1-i];
            reversed[len-1-i] = aux;
        }
        send(c, reversed, sizeof(char) * len, 0);

        free(reversed);
        close(c);
    }
    return 0;
}
*/