#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{

	int p[2];
	pipe(p);
	int a[4] = {1,2,3,4};
	
	if(fork() == 0)
	{
		close(p[0]);
		a[1] += a[3];
		write(p[1], &a[1], sizeof(int));
		close(p[1]);
		exit(0);
	}
	close(p[1]);
	a[0] += a[2];
	wait(0);
	read(p[0], &a[1], sizeof(int));
	close(p[0]);
	a[0] += a[1];
	printf("%d\n", a[0]);	
	return 0;
	
}
