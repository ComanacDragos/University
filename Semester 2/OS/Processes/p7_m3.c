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

//Process C

int main(int argc, char** argv)
{
	int b2c, c2a;
	b2c = open("b2c", O_RDONLY);
	c2a = open("c2a", O_WRONLY);

	int n;
	read(b2c, &n, sizeof(int));	
	printf("C <-- B: %d\n", n);
	
	int min, max;
	int x;
	read(b2c, &x, sizeof(int));
	printf("C <-- B: %d\n",x);

	min = x;
	max = x;
	for(int i=1;i<n;i++)
	{	
		read(b2c, &x, sizeof(int));
		printf("C <-- B: %d\n",x);
		if(min > x)
			min = x;
		if(max < x)
			max = x;
	} 
	printf("C --> A: %d\n", min);
	write(c2a, &min, sizeof(int));
	printf("C --> A: %d\n", max);
	write(c2a, &max, sizeof(int));
	close(b2c); close(c2a);
	
}
