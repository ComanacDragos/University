#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int arg, char**argv)
{
	char s[64], *p;
	while(1)
	{
		p=fgets(s, 64, stdin);
		if(p == NULL)
			break;
		int i;
		for(i=0;i<strlen(s);i++)
			if(s[i] != '\n')
				s[i] = '*';
		fprintf(stdout, "%s", s);
	}

	return 0;
}
