#include <fcntl.h>           /* Definition of AT_* constants */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char** argv)
{

	mkfifo("testFifo", O_RDONLY);
	unlink("testFifo");

	return 0;
}
