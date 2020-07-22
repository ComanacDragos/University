#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "header.h"
//Reader

int main(int argc, char** argv)
{
	abc s;
	int w2r = open("w2r2", O_RDONLY);
	read(w2r, &s, sizeof(abc));
	printf("%d %s %.2f\n", s.a, s.b, s.c);
	return 0;
}
