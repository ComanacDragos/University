#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		fprintf(stderr, "Bad command\n");
		exit(1);
	}

	int p2c[2], c2p[2];
	pipe(p2c);pipe(c2p);
	
	int pid = fork();
	if(pid == -1)
	{
		perror("Error on fork : ");
		exit(1);
	}

	if(pid == 0)
	{
		close(p2c[1]);
		close(c2p[0]);
		int n, s=0, aux;
		if(read(p2c[0], &n, sizeof(int)) < 0)
		{
			perror("Error on read : ");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}

	
		aux = n;
		while(aux)
		{
			int nr;
			if(read(p2c[0], &nr, sizeof(int)) < 0)
			{
				perror("Error on read : ");
				close(p2c[0]);
				close(c2p[1]);
				exit(1);
			}
			printf("Child received: %d\n",nr);
			s += nr;
			aux -= 1;
		}
		float avg=(float)s/n;
		if(write(c2p[1], &avg, sizeof(float)) < 0)
		{
			perror("Error on write : ");
			
			close(p2c[0]);
			close(c2p[1]);
			exit(1);	
		}

		close(p2c[0]);
		close(c2p[1]);
		exit(0);
	}	
	close(p2c[0]);
	close(c2p[1]);
	int n = atoi(argv[1]);
	
	if(write(p2c[1], &n, sizeof(int)) < 0)
	{
		perror("Error on write: ");
		close(p2c[0]);
		close(c2p[1]);
		exit(1);		
	}
	srandom(time(0));
	for(int i=0;i<n;i++)
	{
		int nr = random() % 10;
		printf("Parent sent %d\n", nr);
		if(write(p2c[1], &nr, sizeof(int)) < 0)
		{
			perror("Error on write: ");
			close(p2c[0]);
			close(c2p[1]);
			exit(1);
		}
	}		
	wait(0);
	float avg;	
	if(read(c2p[0], &avg, sizeof(float)) < 0)
	{
		perror("Error on read: ");
		close(p2c[0]);
		close(c2p[1]);
		exit(1);
	}
	printf("Average : %f\n", avg);

	close(p2c[1]);
	close(c2p[0]);
	return 0;
}
