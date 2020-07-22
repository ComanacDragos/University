#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

void play(int read_from, int write_to, int id)
{
	int number = 1;
	srandom(time(0));

	while(number >= 0)
	{
		if(read(read_from, &number, sizeof(int)) < 0)
		{
			perror("Error on read:");
			exit(1);
		}
		if(number == -1)
		{
			printf("%d received -1 Terminating...\n",id);
			if(0>write(write_to, &number, sizeof(int)))
			{
				perror("Error on write");
				exit(1);
			}
			return;
		}
		number += 1;
		if(number%17 == 0)
		{
			int chance = rand() %20;
			if(chance == 0)
				number = -1;
			printf("%d --> Boltz\n", id);
		}
		else
			printf("%d --- %d\n", id, number);
		if(0>write(write_to, &number, sizeof(int)))
		{
			perror("Error on write:");
			exit(1);
		}
	}
	printf("Process %d failed Terminating...\n",id);
}


int main(int argc, char** argv)
{
	int N = atoi(argv[1]);
	
	int p[N][2];

	for(int i=0;i<N;i++)
		pipe(p[i]);
	
	for(int i=1;i<N;i++)
	{
		int pid=fork();
		if(pid == -1)
		{
			perror("Error on fork");
			exit(1);
		}
		if(pid == 0)
		{
			int read_from = p[i][0];
			int write_to = p[(i+1)%N][1];
			play(read_from, write_to, i);
			exit(0);
		}
	}
	int number = 1;
	write(p[1][1], &number, sizeof(int));
	play(p[0][0], p[1][1], 0);

	for(int i=0;i<N;i++)
		wait(0);
	
	for(int i=0;i<N;i++)
	{
	close(p[i][0]);
	close(p[i][1]);
	}

	return 0;
}
