/*
Using PIPE channels create and implement the following scenario: 
Process A reads N integer numbers from the keyboard and sends them another process named B.
 Process B will add a random number, between 2 and 5, to each received number from process A and will 
send them to another process named C.
 The process C will add all the received numbers and will send the result back to process A.
 All processes will print a debug message before sending and after receiving a number.


*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char** argv)
{
	srand(time(0));
	int a2b[2], b2c[2], c2a[2];
	pipe(a2b); pipe(b2c); pipe(c2a);
	
	int pidB = fork();
	if(pidB == -1)
	{
		perror("Error on fork");
		exit(1);
	}
	else if(pidB == 0)
	{
		//ProcessB
		close(a2b[1]); close(b2c[0]); close(c2a[0]); close(c2a[1]);
		int N;
		if(read(a2b[0], &N, sizeof(int)) < 0)
		{
			perror("Error on read");
		}
		printf("B <-- A : %d\n", N);

		printf("B --> C : %d\n", N);
		if(write(b2c[1], &N, sizeof(int)) < 0)
			perror("Error on write");
		
		for(int i=0;i<N;i++)
		{
			int x;
			if(read(a2b[0], &x, sizeof(int))<0)
				perror("Error on read");
			printf("B <-- A : %d\n", x);
			x += rand()%4 + 2;

			printf("B --> C : %d\n", x);
			if(write(b2c[1], &x, sizeof(int))<0)
				perror("Error on write");
		}
		close(a2b[0]); close(b2c[1]);
		printf("Terminating B...\n");
		exit(0);
	}
	int pidC = fork();
	if(pidC == -1)
	{
		perror("Error on fork");
		exit(1);
	}
	else if(pidC == 0)
	{
		//Process C
		close(a2b[0]); close(a2b[1]); close(b2c[1]); close(c2a[0]);
		int N;
		if(read(b2c[0], &N, sizeof(int)) < 0)
			perror("Error on read");
		printf("C <-- B : %d\n", N);
		
		int s = 0;
		for(int i=0;i<N;i++)
		{
			int x;
			if(read(b2c[0], &x, sizeof(int))<0)
				perror("Error in read");
			printf("C <-- B : %d\n", x);
			s += x;
		}
		printf("C --> A : %d\n", s);
		if(write(c2a[1], &s, sizeof(int))<0)
			perror("Error on write");
		close(c2a[1]); close(b2c[0]);
		printf("Terminating C...\n");
		exit(0);
	}
	close(a2b[0]); close(b2c[1]); close(b2c[0]); close(c2a[1]);
	printf("Give N: ");
	int N;
	scanf("%d", &N);
	int v[N];
	for(int i=0;i<N;i++)
	{
		printf("Give x: ");
		scanf("%d",&v[i]);
	}
	printf("A --> B : %d\n", N);
	if(write(a2b[1], &N, sizeof(int))<0)
		perror("Error on write");
	for(int i=0;i<N;i++)
	{
		printf("A --> B : %d\n", v[i]);
		if(write(a2b[1], &v[i], sizeof(int)) < 0)
			perror("Error in write");
	}
	int s;
	if(read(c2a[0], &s, sizeof(int))<0)
		perror("Error on read");
	printf("A <-- C : %d\n", s);
	close(c2a[0]); close(a2b[1]);
	wait(0); wait(0);
	printf("Terminating A...\n");
	return 0;
}

