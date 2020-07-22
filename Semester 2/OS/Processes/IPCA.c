#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
 /*Create two processes A and B. A creates a shared memory segment. 
A then keeps reading strings from the standard input and places whatever it reads in the shared memory segment(replacing previous data). 
Process B, on each run, reads the data from the shared memory segment and counts the number of vowels. 
Process A, upon receiving a SIGINT, deletes the shared memory segment.
*/
//Process A

int shmid=-1;
char* data = (char*)(-1);

void handler (int sig)
{
	printf("YES! %d\n", shmid);
	if(data != (char*)(-1))
		shmdt(data);
	if(shmid != -1)
	{		
		shmctl(shmid, IPC_RMID, NULL);
		printf("YESS\n");
	}

	exit(0);
}

int main(int argc, char** argv)
{
	char s[64];
	signal(SIGINT, handler);
	shmid = shmget(1234, 1024, IPC_CREAT | 0600);
	data = shmat(shmid, 0 ,0);
	printf("%d\n", shmid);
	while(1)
	{	
		int k = read(0, s, sizeof(char)* 64);
		s[k-1] = 0;
		strcpy(data, s);
		
		printf("String: %s written\n", s);
	}
	return 0;
}	



