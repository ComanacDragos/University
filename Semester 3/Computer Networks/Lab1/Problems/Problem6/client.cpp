#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    int c = socket(AF_INET, SOCK_STREAM, 0);

    if(c<0){
        printf("Error on client socket\n");
    }

    struct sockaddr_in server;

    memset(&server, 0, sizeof(server));

    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("192.168.0.115 ");

    char ch, str[256];

    printf("Get string: ");
    fgets(str, 256, stdin);
    str[strlen(str)-1] = NULL;

    printf("Get c: ");
    scanf("%c", &ch);

    if(connect(c, (struct sockaddr*)&server, sizeof(server)) < 0){
        printf("Error on connect\n");
        return 1;
    }

    int res = send(c, &ch, sizeof(char), 0);

    if(res != sizeof(char))
        printf("Error on send\n");

    int len = htonl(strlen(str) + 1);
    res = send(c, (char*)&len, sizeof(len), 0);

    if(res != sizeof(len))
        printf("Error on sending len\n");

    res = send(c, str, sizeof(char) * (strlen(str) + 1), 0);

    if(res != sizeof(char) * (strlen(str) + 1))
        printf("Error on sending string\n");

    res = recv(c, (char*)&len, sizeof(len), 0);

    if(res != sizeof(len))
        printf("Error on receiving len\n");

    len = ntohl(len);

    printf("Received %d\n", len);

    int* arr = (int*)malloc(sizeof(int) * len);

    for(int i=0;i<len;i+=1){
        res = recv(c, (char*)&arr[i], sizeof(int), 0);

        if(res != sizeof(int))
            printf("Error on receiving index\n");
        arr[i] = ntohl(arr[i]);
    }

    printf("Received indexes: ");
    for(int i=0;i<len;i+=1)
        printf("%d ", arr[i]);

    printf("\n");

    close(c);
    free(arr);
    return 0;
}
