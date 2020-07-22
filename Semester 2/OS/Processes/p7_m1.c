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
/*
 Using FIFO channels create and implement the following scenario:
 Process A receives N integer numbers from the command line 
and sends them one by one to another process named B. 
Process B will subtract a random number, between 0 and 2, 
from each received number and will send them to another process named C.
 The process C will establish the minimum and the maximum values from all the received numbers
 and will send them back to process A.
 All processes will print a debug message before sending and after receiving a number.*/

int main(int argc, char** argv)
{
	if(argc <= 1)
		exit(1);

	int a2b, c2a;
	a2b = open("a2b", O_WRONLY);
	c2a = open("c2a", O_RDONLY);
	int i;
	int N = argc-1;
	printf("A -- > B: %d - N\n", N);
	write(a2b, &N, sizeof(int));
	for(i=1;i<argc;i++)
	{
		int n = atoi(argv[i]);
		printf("A --> B: %d\n", n);
		write(a2b, &n, sizeof(int));
	}
	int min, max;
	read(c2a, &min, sizeof(int));
	printf("A <-- C: %d - min\n", min);
	read(c2a, &max, sizeof(int));
	printf("A <-- C: %d - max\n", max);
	close(a2b); close(c2a);
	return 0;
}
