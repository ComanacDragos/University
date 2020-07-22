#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char** argv)
{
	int p2c[2], c2p[2];
	pipe(p2c); pipe(c2p);
	int pid = fork();
	if(pid == -1)
	{
		perror("Error on fork: ");
		exit(1);		
	}
	if(pid == 0)
	{
		close(p2c[1]); close(c2p[0]);
		int a,b;
		while(a+b!=a*b)
		{
			read(p2c[0], &a, sizeof(int));
			read(p2c[0], &b, sizeof(int));
			printf("Child received %d %d\n", a,b);
			int s = a+b, p = a*b;
			write(c2p[1], &s, sizeof(int));
			write(c2p[1], &p, sizeof(int));
		}
		printf("Terminating child...\n");
		close(p2c[0]); close(c2p[1]);
		exit(0);
	}
	close(p2c[0]); close(c2p[1]);
	int a,b,s,p;
	while(1)
	{
		scanf("%d", &a);
		scanf("%d", &b);
		printf("Parent sends %d %d\n", a, b);
		write(p2c[1], &a, sizeof(int));
		write(p2c[1], &b, sizeof(int));
		read(c2p[0], &s, sizeof(int));
		read(c2p[0], &p, sizeof(int));
		printf("Sum: %d  Product: %d\n", s, p);
		if(s == p)
			break;
			
	}
	printf("Terminating parent...\n");
	close(p2c[1]); close(c2p[0]);
	wait(0);
	return 0;
}
