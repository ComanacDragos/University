#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char** argv)
{
	if(argc == 1)
	{
		fprintf(stderr, "Provide command\n");
		exit(1);
	}

	if(fork() == 0)
	{
		if(execvp(argv[1], argv+1) == -1)
		{
			fprintf(stderr, "Exec ran into a problem\n");
			exit(1);
		}
	}
	wait(0);
	printf("The command was successful\n");

	return 0;
}
