#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
void play(int id, int wr, int rd)
{
	char l;
	while(1)
	{	
		if(read(rd, &l, sizeof(char))<0)
			perror("Error on read");
		if( l=='Z')
		{
			if(write(wr,&l,sizeof(char))<0)
				perror("Error on write");
			break; 
		}
		l+=1;
		printf("ID: %d --> %c\n", id, l);
		if(write(wr, &l, sizeof(char))<0)
			perror("Error on write");
		if(l == 'Z')
			break;
	}
	printf("Terminating %d...\n",id);
	close(rd); close(wr);
	exit(0);
}

int main(int argc, char** argv)
{	
	srand(time(0));
	int start = rand()%6;
	printf("Start: %d\n",start);
	int pipes[6][2];
	int i;
	for(i=0;i<6;i+=1)
		if(pipe(pipes[i])==-1)
			perror("Error on pipe");
	char l='A'-1;
	int w=start-1;
	if(w==-1)
		w=5;
	if(write(pipes[w][1], &l, sizeof(char))<0)
		perror("Error on write");
	for(i=0;i<6;i+=1)
	{
		int pid = fork();
		if(pid == -1)
			perror("Error on fork");
		if(pid == 0)
		{
			int wr = start;
			int rd = start-1;
			if(rd == -1)
				rd = 5;
			play(start,pipes[wr][1],pipes[rd][0]);
		}
		start+=1;
		start = start%6;
	}	
	for(i=0;i<6;i+=1)
		wait(0);
	return 0;
}
