#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>                                                                                          
#include <sys/wait.h>
#include <string.h>


int main(int argc, char** argv)
{
	int a2b[2], b2a[2];
	pipe(a2b); pipe(b2a);
	int pid = fork();
	if(pid == -1)
	{
		perror("Error on fork");
		exit(1);
	}
	if(pid == 0)
	{
		close(a2b[1]); close(b2a[0]);
		char c;
		read(a2b[0], &c, sizeof(char));
		while(1)
		{
			
		}
	}
	
}
