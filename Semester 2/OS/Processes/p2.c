#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	int i;
	for(i=0; i<3;i++)
	{
		//int pid;
		//pid = fork();
		if(fork() == 0)
		{
			printf("Current child %d and parent %d\n", getpid(), getppid());
			exit(0);
		}
	}
		
	for(i=0; i<3;i++)
		wait(0);
	return 0;
}
