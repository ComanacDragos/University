/*
8b. Same as 9a, but calculate the sum of all the elements of the matrix using as many threads as there are rows, each thread adds to the total the numbers on a row. Use the test matrix to check if the program is calculating the total sum correctly. The expected result is 1000000. Try with and without mutex.
*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int total=0;
int** matrix, m,n;
pthread_mutex_t mtx;

void* f(void* a)
{
	int i = *(int*)a;
	int sum=0;
	for(int j=0;j<n;j++)
		sum += matrix[i][j];
	pthread_mutex_lock(&mtx);
	total += sum;
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc, char** argv)
{
	FILE* fd = fopen("bigmat", "r");
	fscanf(fd, "%d %d", &m,&n);
	printf("%d %d\n",m,n);
	pthread_mutex_init(&mtx, NULL);
	matrix = (int**)malloc(sizeof(int*)*m);
	for(int i=0;i<m;i++)
	{
		matrix[i] = (int*)malloc(sizeof(int)*n);
		for(int j=0;j<n;j++)
		{
			fscanf(fd,"%d", &matrix[i][j]);
		}
	}
	pthread_t t[m];
	int rows[m];
	for(int i=0;i<m;i++)
	{
		rows[i] =i;
		pthread_create(&t[i],NULL,f, &rows[i]);	
	}
	for(int i=0;i<m;i++)
		pthread_join(t[i], NULL);

	for(int i=0;i<m;i++)
		free(matrix[i]);
	free(matrix);
	pthread_mutex_destroy(&mtx);
	printf("%d\n",total);
	fclose(fd);
	return 0;	
}
