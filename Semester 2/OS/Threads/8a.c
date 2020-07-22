/*
8a. Write a C program that reads a matrix from a file.
 It then creates as many threads as there are rows in the matrix,
 each thread calculates the sum of the numbers on a row. 
The main process waits for the threads to finish, then prints the sums.
*/
#include <pthread.h>
#include  <stdio.h>
#include <stdlib.h>

int m,n;
int* sums, **matrix;

void* f(void* a)
{
	int i=*(int*)a;
	printf("%d\n", i);
	int s=0;
	for(int j=0;j<n;j++)
		s+= matrix[i][j];
	sums[i] = s;
	return NULL;
}


int main(int argc, char** argv)
{
	FILE* fd=fopen("matrix.txt", "r");
	if(fd<0i
	{
		perror("Error on fopen");
		exit(1);
	}
	fscanf(fd, "%d %d", &m, &n);
	printf("%d %d\n", m,n);
	matrix = (int**)malloc(sizeof(int*)*m);
	sums = (int*)malloc(sizeof(int)*m); 
	for(int i=0;i<m;i++)
	{
		matrix[i] = (int*)malloc(sizeof(int)*n);
		for(int j=0;j<n;j++)
	
			fscanf(fd, "%d", &matrix[i][j]);
	}
	for(int i=0;i<m;i++)
		{for(int j=0;j<n;j++)
			printf("%d ", matrix[i][j]);
		printf("\n");
	}
	fclose(fd);
	
	
	pthread_t t[m];
	int ids[m];
	for(int i=0;i<m;i++)
	{
		ids[i] = i;
		pthread_create(&t[i],NULL, f, &ids[i]);
	}
	for(int i=0;i<m;i++)
		pthread_join(t[i], NULL);

	for(int i=0;i<m;i++)
		printf("%d ", sums[i]);

	for(int i=0;i<m;i++)
		free(matrix[i]);	
	free(matrix);
	free(sums);
	return 0;
}

