#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
	int fd;
	if((fd=open("fifo5", O_RDONLY))<0)
	{
		perror("Error on open fifo");
		exit(1);
	}
	while(1)
	{
		int n;
		if(read(fd, &n, sizeof(int))<0)
			perror("Error on read");
		if(n==-1)
			break;
		char* s = (char*)malloc(n*sizeof(char));
		if(read(fd, s, sizeof(char)*n)<0)
			perror("Error on read message");
		printf("%s", s);
		free(s);
	}
	close(fd);
	return 0;
}
