#include <unistd.h>
#include <string.h>

int main(int argc, char** argv)
{
	char s[64];
	
	while(1)
	{
	int k;
	if((k=read(0, s, 64)) < 0)
		break;
	int i;
	for(i=0;i<strlen(s);i++)
		if(s[i] != '\n')
			s[i] = '*';
	write(1, s, k);
	}
	
	return 0;
}

