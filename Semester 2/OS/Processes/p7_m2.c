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

//Process B

int main(int argc, char** argv)
{
	int a2b, b2c;
	a2b = open("a2b", O_RDONLY);
	b2c = open("b2c", O_WRONLY);
	srand(time(0));
	int n;
	read(a2b, &n, sizeof(int));
	printf("B <-- A: %d\n", n);
	printf("B --> C: %d\n", n);
	write(b2c, &n, sizeof(int));
	for(int i=0;i<n;i++)
	{
		int x;
		read(a2b, &x, sizeof(int));
		printf("B <-- A: %d\n", x);
		x += rand()%3;
		printf("B --> C: %d\n", x);
		write(b2c, &x, sizeof(int));
	}
	close(a2b); close(b2c);
	return 0;
}
