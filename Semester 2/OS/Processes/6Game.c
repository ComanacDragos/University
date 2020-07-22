#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

void play(int id, int wr, int rd)
{
	printf("%d starts\n",id);
	int i;
	for(i=0;i<6;i+=1)
	{
		int n;
		if(read(rd, &n, sizeof(int))<0)
			perror("Error on read");
		printf("%d <-- %d\n", id, n);
		int ok=0, aux=n;
		if(n%6==0)
			ok=1;
		else
		{
			while(n && ok == 0)
			{
				if(n%10==6)
					ok=1;
				n/=10;
			}
		}
		if(ok==1)
			printf("%d %d--> BINGO!\n", id, aux);
		aux+=1;
		printf("%d --> %d\n", id, aux);
		if(write(wr, &aux, sizeof(int))<0)
			perror("Error on write");
	}	
	printf("Terminating %d...\n", id);
	close(rd);close(wr);
}

int main(int argc, char** argv)
{
	int a2b, b2c, c2a;
	if(mkfifo("a2b", 0600)<0)
		perror("Error on mkfifo");
	mkfifo("b2c", 0600);
	mkfifo("c2a", 0600);

	int pidB=fork();
	if(pidB==-1)
		perror("Error on fork");
	if(pidB==0)
	{	
		if((b2c=open("b2c", O_WRONLY))<0)
			perror("Error on open fifo");
		
		if((a2b=open("a2b", O_RDONLY))<0)
			perror("Error on open fifo");
		play(2, b2c, a2b);
		exit(0);
	}
	int pidC=fork();
	if(pidC==-1)
		perror("Error on fork");
	if(pidC==0)
	{
		if((c2a=open("c2a", O_WRONLY))<0)
			perror("Error on open fifo");
		if((b2c=open("b2c", O_RDONLY))<0)
			perror("Error on open fifo");
		
		play(3, c2a, b2c);
		exit(0);
	}

	int n;
	printf("Give n: ");
	scanf("%d", &n);


	if((c2a=open("c2a", O_RDONLY))<0)
		perror("Error on open fifo");
	
	if((a2b=open("a2b", O_WRONLY))<0)
		perror("Error on open fifo");
	int i, id =1;	
	for(i=0;i<6;i+=1)
	{
		printf("%d --> %d\n", id, n);
		if(write(a2b, &n, sizeof(int))<0)
			perror("Error on write");

		if(read(c2a, &n, sizeof(int))<0)
			perror("Error on read");
		printf("%d <-- %d\n", id, n);
	
		int ok=0, aux=n;
		if(aux%6==0)
			ok=1;
		else
		{
			while(aux && ok == 0)
			{
				if(aux%10==6)
					ok=1;
				aux/=10;
			}
		}
		if(ok==1)
			printf("%d %d--> BINGO!\n", id, n);
		n+=1;
	}	
	
	
	printf("BEFORE WAIT\n");	
	wait(0);wait(0);
	printf("END\n");
	unlink("a2b");
	unlink("b2c");
	unlink("c2a");
	return 0;
}
