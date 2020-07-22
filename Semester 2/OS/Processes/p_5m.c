/*
5. Write two C programs that communicate via fifo. Program A is responsible for creating/deleting the fifo. Program A reads commands from the standard input, executes them and sends the output to program B. Program B keeps reading from the fifo and displays whatever it receives at the standard output. This continues until program A receives the "stop" command.
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SIZE 100

void write_to_fifo(int fd, char* buf)
{
	int nr = strlen(buf);
	if(write(fd, &nr, sizeof(int))<0)
		perror("Error on write size to fifo");
	if(write(fd, buf, sizeof(char)*nr)<0)
		perror("Error on write buf to fifo");
}

int main(int argc, char** argv)
{
	mkfifo("fifo5", 00600);
	char* s =(char*)malloc(sizeof(char)*SIZE);
	memset(s, 0, SIZE*sizeof(char));
	char* buf = (char*)malloc(sizeof(char)*SIZE);
	memset(buf, 0, SIZE*sizeof(char));
	int fd;
	if((fd=open("fifo5", O_WRONLY))<0)
	{
		perror("Error on open fifo");
		exit(1);
	}
	int k;
	while(1)
	{
		if((k=read(0,s, SIZE*sizeof(char)))<0)
			perror("Error");
		s[k-1]=0;
		if(strcmp(s, "stop")==0)
			break;
		FILE* f = popen(s, "r");
		
		while(fread(buf, 1, SIZE-1, f)>0)
		{
			write_to_fifo(fd, buf);
			memset(buf, 0, SIZE*sizeof(char));
		}
		pclose(f);
	}
	int stop = -1;
	if(write(fd, &stop, sizeof(int))<0)
		perror("Error on size write");
	close(fd);
	unlink("fifo5");	
	free(s);
	free(buf);
}
