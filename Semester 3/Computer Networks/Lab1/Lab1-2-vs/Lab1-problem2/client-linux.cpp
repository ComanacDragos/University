#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
// for inet_ntoa
#include <arpa/inet.h>
// for close
#include <unistd.h>

#include <string.h>

int main(){
    printf("Start reading: ");

    char s[256];
    fgets(s, 256, stdin);

    printf("Done reading...\n");


    int c = socket(AF_INET, SOCK_STREAM, 0);

    if(c<0){
        printf("Error on client socket\n");
        return 1;
    }

    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));

    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.0.115");

    if(connect(c, (struct sockaddr*)& server, sizeof(server)) < 0){
        printf("Error on connecting to server\n");
        return 1;
    }

    printf("Done connecting\n");
    printf("Sending %d and %s\n", strlen(s), s);
    int len = htons(strlen(s));

    int res = send(c, (char*)&len, sizeof(len), 0);

    if(res != sizeof(len))
        printf("Error on sending len");

    res = send(c, s, sizeof(char) * len, 0);

    int spaces;

    res = recv(c, (char*)&spaces, sizeof(spaces), 0);

    if(res != sizeof(spaces))
        printf("Error on receiving data");

    spaces = ntohs(spaces);

    printf("The number of blank spaces is %d\n", spaces);

    close(c);

    return 0;
}
