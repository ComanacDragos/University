/*
6. Create two processes A and B. A generates a random number n between 50 and 200. If it is even, it sends it to B, if it is odd it sends n+1 to B. B receives the number and divides it by 2 and sends it back to A. The process repeats until n is smaller than 5. The processes will print the value of n at each step.
*/
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
	srand(time(0));
	int pid=fork();
	if(pid == -1)
	{
		perror("Error on fork");
		exit(1);
	}
	else if(pid == 0)
	{
		//child
		int n;
		close(a2b[1]); close(b2a[0]);
		while(1)
		{
			if(read(a2b[0], &n, sizeof(int))<0)
				perror("Error on read");
			if(n<=5)
				break;
			n /=2;
			printf("B --> A : %d\n", n);	
			if(write(b2a[1], &n, sizeof(int))<0)
				perror("Error on write");
		}
		close(a2b[0]); close(b2a[1]);
		printf("Terminating B ...\n");
		exit(0);
	}
	close(a2b[0]); close(b2a[1]);
	int n = rand()%151 + 50;
	printf("Start: %d\n", n);
	while(1)
	{	
		n+=n%2;
		printf("A --> B : %d\n", n);
		if(write(a2b[1], &n, sizeof(int))<0)
			perror("Error on write");
		if(read(b2a[0], &n, sizeof(int))<0)
			perror("Error on read");	
		if(n<=5)
			break;
	}
	close(a2b[1]); close(b2a[0]);
	printf("Terminating A...\n");
	return 0;

}
