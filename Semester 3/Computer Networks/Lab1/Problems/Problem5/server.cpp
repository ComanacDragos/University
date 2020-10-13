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

int main(){
    int s = socket(AF_INET, SOCK_STREAM, 0);

    if(s<0){
        printf("Error on server socket");
        return 1;
    }

    struct sockaddr_in server, client;
    int c, err, l;
    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    if(bind(s, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Error on bind\n");
        return 1;
    }

    listen(s, 5);
    l = sizeof(client);
    memset(&client, 0, sizeof(client));
    printf("Listening for incoming connections\n");
    while(1){
        c = accept(s, (struct sockaddr*)&client, (socklen_t*)&l);

        err = errno;

        if(c<0){
            printf("Accept error: %d", err);
            continue;
        }

        printf("Incoming connected client from %s:%d\n",
            inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        int nr;
        int res = recv(c, (char*)&nr, sizeof(nr), 0);

        if(res != sizeof(nr))
            printf("Error on nr\n");

        nr = ntohl(nr);
        printf("Received: %d\n", nr);

        int* v = (int*)malloc(sizeof(int) * ((1 + nr/2)));
        int k=0;
        for(int i=1;i<=nr/2;i+=1)
            if(nr%i == 0)
              v[k++] = i;
        v[k++] = nr;
        int aux = htonl(k);

        send(c, (char*)&aux, sizeof(aux), 0);

        for(int i=0;i<k;i+=1){
            aux = htonl(v[i]);
            send(c, (char*)&aux, sizeof(aux), 0);
        }
        free(v);
        close(c);
    }

}
*/