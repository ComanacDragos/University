#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char** argv)
{
	srand(time(0));
	int fd = open("matrix.bin", O_CREAT | O_WRONLY);	
	for(int i=0;i<10000;i++)
	{
		int n =rand();
		write(fd, &n, sizeof(char));
	}
	return 0;
}

