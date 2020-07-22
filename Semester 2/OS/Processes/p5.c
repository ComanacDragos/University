#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


void handler (int sgn)
{
	char s[32];
	printf("Are you sure you want me to stop?(y/n)\n");
	scanf("%s", s);
	if(strcmp(s, "y") == 0)
		exit(0);	
}

int main (int argc, char** argv)
{


	void (*f)(int) = &handler;
	signal(SIGINT, f);
	while(1)
	{
 	char s[32];
	int k=read(0, s, 32);
	char c='0'+k;
	write(1, &c, 1);	
	write(1, s, k);

	}
	return 0;
}
