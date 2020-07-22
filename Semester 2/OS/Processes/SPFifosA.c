#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
//Program A
int main(int argc, char** argv)
{
	int a2b = open("a2b", O_WRONLY);
	int b2a = open("b2a", O_RDONLY);

	while(1)
	{
		printf("Give numbers: \n");
		int a,b,s,p;
		scanf("%d", &a);
		scanf("%d", &b);
		printf("A sends %d %d\n", a, b);
		write(a2b, &a, sizeof(int));
		write(a2b, &b, sizeof(int));
 		read(b2a, &s, sizeof(int));
		read(b2a, &p, sizeof(int));
		printf("Sum: %d Product: %d\n", s, p);
		if(s==p)
			break;
	}
	printf("Terminating A...\n");
	close(a2b); close(b2a);
	return 0;
}
