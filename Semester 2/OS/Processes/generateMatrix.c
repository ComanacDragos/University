#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char** argv)
{
	int fd = open("matrix.bin", O_CREAT|O_WRONLY);
	srand(time(0));
	for(int i=0;i<2000;i++)
	{
		int x = rand()%2000;
		write(fd, &x, sizeof(int));
	}
	close(fd);
	
}
