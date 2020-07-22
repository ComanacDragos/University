#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

int main(int argc, char** argv)
{
	if(argc < 2)
	{
		fprintf(stderr, "No command provided\n");
		exit(1);
	}
	int status;
	for(int i=1;i<argc;i++)
	{
		if(fork() == 0)
		{
			if(execlp(argv[i], argv[i], NULL) == -1)
			{
				fprintf(stderr, "Err on execvp Failed to execut %s : %s\n", argv[i], strerror(errno));
				exit(0);
			}
		}
		wait(&status);
		if(WEXITSTATUS(status) != 0)
		{
		fprintf(stderr, "Program \"%s\" failed with exit code %d\n", argv[i], WEXITSTATUS(status));
		}
	}

	return 0;
}

int ma2in(int argc, char** argv) {
 int i, status;
 for(i=1; i<argc; i++) {
 if(fork() == 0) {
 if(execlp(argv[i], argv[i], NULL) == -1) {
 fprintf(stderr, "Failed to execute program \"%s\": %s\n", argv[i], strerror(errno));
 exit(0);
 }
 }
 wait(&status);
 if(WEXITSTATUS(status) != 0) {
 fprintf(stderr, "Program \"%s\" failed with exit code %d\n", argv[i], WEXITSTATUS(status));
 }
 }
 return 0;
}
