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
        int a2b = open("a2b", O_RDONLY);
        int b2a = open("b2a", O_WRONLY);

	while(1)
	{
		int a,b,s,p;
		read(a2b, &a, sizeof(int));
		read(a2b, &b, sizeof(int));
		s = a+b;
		p = a*b;
		printf("B send %d %d\n", s, p);
		write(b2a, &s, sizeof(int));
		write(b2a, &p, sizeof(int));
		if(s==p)
			break;
	}
	printf("Terminating B...\n");
	close(a2b); close(b2a);
	return 0;
}
