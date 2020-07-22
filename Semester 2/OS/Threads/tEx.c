#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int neg= 0, v[10];
pthread_rwlock_t rwl[10];
pthread_mutex_t mtx;

void* decrementer(void*a)
{
	int i;
	for(i=0;i<100;i+=1)
	{
		srand(time(0)+i);
		int index = rand()%10;
		pthread_rwlock_wrlock(&rwl[index]);
		v[index] -= 1;
		pthread_rwlock_unlock(&rwl[index]);
		
	}
	return NULL;
}

void* adder(void*a)
{
	int i,j, aux=0;
	for(i=0;i<1000;i++)
	{	
		for(j=0;j<10;j++)
		{
		
			pthread_rwlock_rdlock(&rwl[j]);
			if(v[i]<0)
				aux += v[i];
			pthread_rwlock_unlock(&rwl[j]);
		}	
	}
	printf("%d\n\n", aux);

	pthread_mutex_lock(&mtx);
	neg += aux;
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}


int main(int argc, char** argv)
{
	srand(time(0));
	int i;
	pthread_t t1[10], t2[10];
	pthread_mutex_init(&mtx, NULL);
	for(i=0;i<10;i+=1)
	{
		v[i] = rand()%100;
		pthread_rwlock_init(&rwl[i], NULL);
	}
	for(int i=0;i<10;i++)
		printf("%d ", v[i]);
	printf("\n");
	for(i=0;i<10;i+=1)
	{
		pthread_create(&t1[i], NULL, decrementer, NULL);
		pthread_create(&t2[i], NULL, adder, NULL);
	}
	for(i=0;i<10;i+=1)
	{
		pthread_join(t1[i], NULL);
		pthread_join(t2[i], NULL);
	}
	for(i=0;i<10;i++)
		pthread_rwlock_destroy(&rwl[i]);
	pthread_mutex_destroy(&mtx);
	printf("%d\n", neg);	
	for(int i=0;i<10;i++)
		printf("%d ", v[i]);
	printf("\n");
	
}
