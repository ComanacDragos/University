#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** matrix;
int total=0;

pthread_barrier_t barrier;
pthread_mutex_t mtx, mtxM[10], printM;

void* f(void* a)
{
	int** local = (int**)malloc(sizeof(int*)*10);
	int i;
	for(i=0;i<10;i+=1)
	{
		local[i]= (int*)malloc(sizeof(int)*31);
		local[i][0]=0;
	}	
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if(total==30)
			break;
		else
			total += 1;
		pthread_mutex_unlock(&mtx);
		int x = rand()%1000;
		if(x<10)
		{
			local[0][0] += 1;
			int pos = local[0][0];
			local[0][pos] = x;
	
		}
		else
		{
			int aux = x;
			while(aux > 9)
				aux/=10;
			local[aux][0] += 1;
			int pos = local[aux][0];
			local[aux][pos] = x;	
		}
	}
	pthread_mutex_unlock(&mtx);
	
	for(i=0;i<10;i+=1)
	{
		int j;
		pthread_mutex_lock(&mtxM[i]);
		for(j=0;j<local[i][0];j+=1)
		{
			matrix[i][0]+=1;
			matrix[i][ matrix[i][0] ] = local[i][j+1];		
		}			
		pthread_mutex_unlock(&mtxM[i]);
	}
	
	
	for(i=0;i<10;i++)
		free(local[i]);
	free(local);

	pthread_barrier_wait(&barrier);
		
	int linie = (int)a;
	pthread_mutex_lock(&printM);
	printf("Linia %d ", linie);
	printf(" Nr el: %d El: ", matrix[linie][0]);
	for(i=1;i<=matrix[linie][0];i+=1)
		printf("%d ", matrix[linie][i]);
	printf("\n");
	pthread_mutex_unlock(&printM);
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t t[10];
	srand(time(0));
	matrix = (int**)malloc(sizeof(int*)*10);
	if(pthread_mutex_init(&mtx, NULL)!=0)
		perror("Error on mutex init");
	if(pthread_barrier_init(&barrier, NULL, 10)!=0)
		perror("Error on barrier init");
	if(pthread_mutex_init(&printM, NULL)!=0)
		perror("Error on mutex init");
	int i;
	for(i=0;i<10;i+=1)
	{
		matrix[i]= (int*)malloc(sizeof(int)*31);
		matrix[i][0]=0;
	}
	for(i=0;i<10;i+=1)
	{
		if(pthread_mutex_init(&mtxM[i],NULL)!=0)
			perror("Error on mutex init");	

		if(pthread_create(&t[i], NULL, f, (int*)i)!=0)
			perror("Error on thread create");
	}
	for(i=0;i<10;i+=1)
		if(pthread_join(t[i],NULL)!=0)
			perror("Error on join");

	for(i=0;i<10;i+=1)
	{
		if(pthread_mutex_destroy(&mtxM[i])!=0)
			perror("Error on destroy");
		free(matrix[i]);
	}	
	free(matrix);
	if(pthread_mutex_destroy(&mtx)!=0)
		perror("Error on mutex destroy");
	if(pthread_barrier_destroy(&barrier)!=0)
		perror("Error on destroy barrier");
	if(pthread_mutex_destroy(&printM)!=0)
		perror("Error on mutex destroy");
	return 0;
}
