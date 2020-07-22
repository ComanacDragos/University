#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char** argv)
{
	int a2b[2], b2a[2];
	pipe(a2b); pipe(b2a);
	int pid = fork();
	if(pid == -1)
	{
		perror("Error on fork");
		exit(1);
	}
	if(pid == 0)
	{
		//Process B
		close(a2b[1]);	close(b2a[0]);
		int n;
		while(1)
		{
			if(read(a2b[0], &n, sizeof(int))<0)
			{
				perror("Error on read in B");
			}
			if(n>=35)
				break;
			n *= 2;
			printf("B --> %d\n", n);
			if(write(b2a[1], &n, sizeof(int))<0)
				perror("Error on write in B");
		}
		close(a2b[0]); close(b2a[1]);
		printf("Terminating B...\n");
		exit(0);
	}
	//Process A
	close(a2b[0]); close(b2a[1]);
	srand(time(0));
	int n=rand()%5;
	
	while(1)
	{
		printf("A --> %d\n", n);
		if(write(a2b[1], &n, sizeof(int))<0)
			perror("Error on write in A");
		if(read(b2a[0], &n, sizeof(int))<0)
			perror("Error on read in A");
		if(n>=35)
			break;
		n+=1;	
	}
	close(a2b[1]); close(b2a[0]);
	printf("Terminating A...\n");
	return 0;
}
