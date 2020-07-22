#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//Process B

int main(int argc, char** argv)
{
	char* data;
	int shmid = shmget(1234, 0, 0);
	data = shmat(shmid, 0, 0);	
	printf("Received %s\n", data);

	shmdt(data);
	return 0;
}
