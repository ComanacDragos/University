#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv)
{
	if(argc != 1)
	{
		printf("Bad number of arguments\n");
		exit(1);
	}
	int a2b[2], b2a[2];
	pipe(a2b); pipe(b2a);
	int pid1 = fork();
	if(pid1 == -1)
	{
		perror("Error on fork: ");
		exit(1);
	}
	if(pid1 == 0) //Process A
	{
		close(a2b[0]); close(b2a[1]);
		srandom(time(0));
		int n = random() % 10 + 1;
		while(n==10)
			n = random() % 10 +1;
		if(write(a2b[1], &n, sizeof(int)) < 0)
		{
			perror("Error on write in process A: ");
			exit(1);
		}
		while(1)
		{
			if(read(b2a[0], &n, sizeof(int)) < 0)
			{
				perror("Error on read in process A: ");
				exit(1);
			}
			printf("Process A received: %d\n", n);
			if(n == 10)
				break;
			n = random() % 10 + 1;
			if(write(a2b[1], &n, sizeof(int))<0)
			{
				perror("Error on write in process A: ");
				exit(1);
			}
		}
		printf("Terminating process A...\n");
		close(a2b[1]); close(b2a[0]);
		exit(0);		
	}
	
	pid1 = fork();
	if(pid1 == -1)
	{
		perror("Error on fork: ");
		exit(1);
	}
	if(pid1 == 0)
	{
		int n;
		close(a2b[1]); close(b2a[0]);
		while(1)
		{
			if(read(a2b[0], &n, sizeof(int)) < 0)
			{
				perror("Error on read in process B: ");
				exit(1);
			}
			printf("Process B received %d\n", n);
			if(n == 10)
				break;
			n = random()%10 +1;
			if(write(b2a[1], &n, sizeof(int)) < 0)
			{
				perror("Error on write in process B: ");
				exit(1);	
			}
		}
		printf("Terminating process B...\n");
		close(a2b[0]); close(b2a[1]);
		
	}
	close(a2b[0]); close(a2b[1]);
	close(b2a[0]); close(b2a[1]);
	wait(0);
	wait(0);
	return 0;
}
