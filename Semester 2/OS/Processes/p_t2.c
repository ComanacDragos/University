#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char** argv)
{
	int p2c[argc-1][2];
	for(int i=0;i<argc-1;i++)
		pipe(p2c[i]);
	for(int i=0;i<argc-1;i++)
	{
		int pid = fork();
		if(pid == -1)
		{
			perror("Error on fork");
			exit(1);
		}	
		if(pid == 0)
		{
			for(int j=0;j<argc-1;j++)
			{
				close(p2c[j][0]);
				if(j!=i)
					close(p2c[j][1]);
			}
			int n =0;
			for(int j=0;j<strlen(argv[i+1]);j++)
			{
				if(argv[i+1][j] < '0' || argv[i+1][j] > '9')
				{
					printf("Process %d --> %d\n", i, n);	
					if(write(p2c[i][1], &n, sizeof(int))<0)
						perror("Error on write");
					close(p2c[i][1]);
					exit(0);
				}
			}
			n = atoi(argv[i+1]);
			printf("Process %d --> %d\n", i, n);	
			if(write(p2c[i][1], &n, sizeof(int))<0)
				perror("Error on write");
			close(p2c[i][1]);
			exit(0);
		}
	}
	for(int i=0;i<argc-1;i++)
		close(p2c[i][1]);
	int sum = 0;
	for(int i=0;i<argc-1;i++)
		wait(0);	
	for(int i=0;i<argc-1;i++)
	{
		int x;
		if(read(p2c[i][0], &x, sizeof(int))<0)
			perror("Error on read");
		printf("Received %d\n",x);
		sum += x;
		close(p2c[i][0]);
	}
	printf("Sum: %d\n", sum);
	return 0;
}
