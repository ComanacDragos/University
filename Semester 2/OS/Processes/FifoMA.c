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
//A

 /*Create two processes A and B. A generates a random number n between 50 and 200. 
If it is even, it sends it to B, if it is odd it sends n+1 to B.
 B receives the number and divides it by 2 and sends it back to A.
 The process repeats until n is smaller than 5. 
The processes will print the value of n at each step.*/

int main(int argc, char** argv)
{
	int a2b = open("a2b", O_WRONLY);	
	int b2a = open("b2a", O_RDONLY);
	srand(time(0));
	int n= rand()%151 + 50;
	printf("Start: %d\n", n);
	while(1)
	{
		n+=n%2;
		printf("A sends %d\n", n);
		write(a2b, &n, sizeof(int));
		read(b2a, &n, sizeof(int));
		if(n<=5)
			break;

	}
	close(a2b); close(b2a);
	printf("Terminating...\n");
	return 0;
}
