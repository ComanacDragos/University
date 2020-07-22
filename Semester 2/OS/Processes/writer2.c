#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
//Writer

int main(int argc, char** argv)
{
	int w2r;
	abc s;
	s.a = 5;
	strcpy(s.b, "henlo");
	s.c = 4.4;
	w2r = open("w2r2", O_WRONLY);
	write(w2r, &s, sizeof(abc));
	return 0;
}
