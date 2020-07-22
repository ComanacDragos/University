#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
//Reader
int main(int argc, char** argv)
{
	int w2r, n;
	w2r = open("w2r", O_RDONLY);
	read(w2r, &n, sizeof(int));
	char* s=(char*)malloc(n*sizeof(char));
	read(w2r, s, n*sizeof(char));
	printf("%s\n", s);
	free(s);
	return 0;
}
