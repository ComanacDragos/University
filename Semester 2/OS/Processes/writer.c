#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
//Writer
int main(int argc, char** argv)
{
	int w2r,n;
	w2r=open("w2r", O_WRONLY);
	char s[20] ="Hello there";
	n = strlen(s) + 1;
	write(w2r, &n, sizeof(int));
	write(w2r, s, n*sizeof(char));
	close(w2r);
	return 0;
}
