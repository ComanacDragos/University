#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	int p2a[2], a2b[2], b2p[2];
	pipe(p2a); pipe(a2b); pipe(b2p);

	if(fork() == 0) // Process A
	{
		close(p2a[1]); close(b2p[0]);
		close(a2b[0]); close(b2p[1]);
	
		int n;
		while(1)
		{	
			if(read(p2a[0], &n, sizeof(int)) <= 0)
				break;
			if(n <= 0)
				break;
			n-=1;
			printf("Process A: %d\n", n);
			write(a2b[1], &n, sizeof(int));
		
		clos(p2[0]);
		close(a2b[1]);
		printf("Terminating A...\n");
		exit(0);
	}

	if(fork() == 0) // Process B
	{
		close(a2b[1]); close(p2a[0]);
		close(b2p[0]); close(p2a[1]);
		int n;
		while(1)
		{
			if(read(a2b[0], &n, sizeof(int)) <= 0)
				break;
			if(n <= 0)
				break;
			n -= 1;
			printf("Process B: %d\n", n);
			write(b2p[1], &n, sizeof(int));	
		}
		close(a2b[0]);
		close(b2p[1]);
		printf("Terminating B...\n");
		exit(0);
	}
	
	close(p2a[0]); close(a2b[0]);
	close(b2p[1]); close(a2b[1]);

	int n = atoi(argv[1]);	
	printf("Start : %d\n", n);
	write(p2a[1], &n, sizeof(int));
	while(1)
	{
		if(read(b2p[0], &n, sizeof(int)) <= 0)
			break;
		if(n<=0)
			break;
		n -= 1;
		printf("Parent: %d\n", n);
		write(p2a[1], &n, sizeof(int));
	}
	close(p2a[1]);
	close(b2p[0]);
	wait(0); wait(0);
	
	printf("Terminating parent...\n");
	return 0;
}
