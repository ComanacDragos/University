#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int c=0;
void f(int n)
{
	if(n>0)
	{
		int pid;
		pid = fork();
		if(pid == 0)
		{
			c+=1;
			printf("%d Child: %d Parent: %d N: %d\n", c, getpid(), getppid(), n);
			f(n-1);
		}
	wait(0);
	}
}

int main(int argc, char** argv)
{
	f(4);
	return 0;
}
