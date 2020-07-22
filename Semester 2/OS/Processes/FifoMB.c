#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <time.h>

int main(int argc, char** argv)
{
	int a2b = open("a2b", O_RDONLY);
	int b2a = open("b2a", O_WRONLY);
	int n;
	while(1)
	{
		read(a2b, &n, sizeof(int));
			
		if(n<=5)
			break;
		n/=2;
		printf("B send %d\n", n);
		write(b2a, &n, sizeof(int));
	}
	close(a2b); close(b2a);
	printf("Terminating...\n");
	return 0;
}
