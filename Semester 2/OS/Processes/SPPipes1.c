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
}
