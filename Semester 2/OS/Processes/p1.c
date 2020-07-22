#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char** argv)
{
	int pid;
	//pid = fork();
	if(fork() == 0)
	{
		printf("Child code\n");
		exit(0);
	}
	printf("Parent code \n");
	wait(0);
	return 0;
}


