#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	int i;
	for(i=0;i<3;i++)
	{
		if(fork() == 0)
		{
			
			printf("%d %d %d\n", getppid(), getpid(), i);
			int j;
			for(j=0;j<3;j++)
			{
				if(fork() == 0)
				{
					printf("%d %d %d\n", getppid(), getpid(), j);
					exit(0);
				}
			}
			for(j=0;j<3;j++)
				wait(0);
			printf("\n");
			exit(0);
		}
	}
	for(i=0;i<3;i++)
		wait(0);
	

	return 0;
}
