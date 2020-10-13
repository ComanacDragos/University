/*#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(){
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

    char s1[256], s2[256], *s3;

    printf("s1: ");
    fgets(s1, 256, stdin);
    s1[strlen(s1) - 1] = NULL;

    printf("s2: ");
    fgets(s2, 256, stdin);
    s2[strlen(s2) - 1] = NULL;

    if(connect(c, (struct sockaddr*) & server, sizeof(server)) < 0){
        printf("Error on connecting to server\n");
        return 1;
    }

    int len = htonl(strlen(s1) + 1);

    send(c, &len, sizeof(len), 0);

    send(c, s1, strlen(s1) + 1, 0);

    len = htonl(strlen(
*/