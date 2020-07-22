#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int children[3];

void hp(int sgn)
{
	if(sgn == SIGUSR1)
	{	
		for(int i=0;i<3;i++)
		{
			printf("%d: Sending SIGUSR2\n", getpid());
			kill(children[i], SIGUSR2);
		}
	}
	if(sgn == SIGUSR2)
	{
		for(int i=0;i<3;i++)
		{
			printf("%d: Received SIGKILL\n", getpid());
			kill(children[i], SIGKILL);
		}
	}
}

void hc(int sgn)
{
	if(sgn == SIGUSR2)
		printf("%d: Received SIGUSR2\n", getpid());
}

int main(int argc, char** argv)
{
	int i;
	signal(SIGUSR1, hp);
	signal(SIGUSR2, hp);
	for(i=0;i<3;i++)
	{
		children[i] = fork();
		if(children[i] == 0)
		{
			signal(SIGUSR2, hc);
			while(1);
			exit(0);
		}	
	}
	for(i=0;i<3;i++)
		wait(0);
	return 0;
}
