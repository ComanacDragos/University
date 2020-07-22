#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
//Process A
int main(int argc, char** argv)
{
	int a2b, b2a, n=20;
	a2b = open("a2b", O_WRONLY);
	b2a = open("b2a", O_RDONLY);
	
	write(a2b, &n, sizeof(int));
	printf("A --> %d\n", n);
	while(1)
	{
		if(read(b2a, &n, sizeof(int)) < 0)
		{
			perror("Error on read: ");
			exit(1);
		}
		if(n<=0)
			break;
		n -= 1;
		printf("A --> %d\n", n);
		if(write(a2b, &n, sizeof(int)) < 0)
			break;
	}
	close(a2b); close(b2a);

	return 0;
}
