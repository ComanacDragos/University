#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(int argc, char** argv)
{
	char* s= (char*)malloc(sizeof(char)*256);
	
	//scanf("%s", s);
	int k;
	if((k=read(0, s, sizeof(char)*256))<0)
		perror("Error on read");
	s[k-1] = 0;	

	printf("%s\n%d", s,k);
	free(s);
	return 0;
}
