#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

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
		//process b;
		close(a2b[1]); close(b2a[0]);
		int n;
		if(read(a2b[0], &n, sizeof(int))<0)
			perror("Error on read");

		while(1)
		{
			int x;
			if(read(a2b[0], &x, sizeof(int))<0)
				perror("Error on read");
			if(x<n)
				printf("Mai mic\n");
			if(x>n)
				printf("Mai Mare\n");
			if(x == n)
			{
				printf("Ai ghicit\n");
				break;
			}
		
		}
		printf("Terminating B...\n");
		close(a2b[0]); close(b2a[1]);
		exit(0);
	}
	close(a2b[0]); close(b2a[1]);
	srand(time(0));	
	int n = rand()%50;
	if(write(a2b[1], &n, sizeof(int))<0)
		perror("Error on write");

	while(1)
	{
		int x;
		printf("X: ");
		scanf("%d", &x);
		if(write(a2b[1], &x, sizeof(int))<0)
			perror("Error on write");
		if(n == x)
			break;
	}	
	printf("Terminating... A");
	close(a2b[1]); close(b2a[0]);
	return 0;
}
