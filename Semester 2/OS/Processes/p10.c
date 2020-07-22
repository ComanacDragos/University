#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{	
	if(argc != 2)
	{
		fprintf(stderr, "Bad arguments\n");
		exit(1);
	}
	int pid, p2c[2], c2p[2];
	pipe(p2c);
	pipe(c2p);
	pid = fork();
	if(pid == -1)
	{
		perror("Error on fork: ");
		exit(1);
	}
	if(pid == 0)
	{
		close(p2c[1]);
		close(c2p[0]);
		int n;
		while(n)
		{
			read(p2c[0], &n, sizeof(int));
			n -= 1;
			printf("Chilld : %d\n", n);
			write(c2p[1], &n, sizeof(int));
		}
		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}
	close(p2c[0]);
	close(c2p[1]);
	int n=atoi(argv[1]);
	printf("Start : %d\n", n);
	while(n)
	{
	n -= 1;
	printf("Parent : %d\n", n);
	write(p2c[1], &n, sizeof(int));
	read(c2p[0], &n, sizeof(int));
	}
	close(p2c[1]);
	close(c2p[0]);
	wait(0);
	return 0;
}
