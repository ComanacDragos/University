#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
int main(int argc, char** argv)
{
	int i;
	for(i=0;i<4;i+=1){
	if(fork()&&i%2==1)
		break;	
	}

	
	//printf("%d %d\n", getpid(), getppid());
	printf("A\n");
	wait(0);
	wait(0);
	wait(0);
	wait(0);
	return 0;
}
