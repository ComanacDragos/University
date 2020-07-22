#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int nr1, nr2;
pthread_rwlock_t rwl;
pthread_mutex_t mtx;

void* f(void* a)
{
	srand(time(0));
	while(1)
	{
		int nr = rand()%100;

		pthread_rwlock_rdlock(&rwl);
		if(nr1 == 5)
		{
			pthread_rwlock_unlock(&rwl);
			break;
		}
		pthread_rwlock_unlock(&rwl);

		if(nr<10)
		{
			pthread_rwlock_wrlock(&rwl);
			nr1+=1;
			pthread_rwlock_unlock(&rwl);
		}
		else
		{
			pthread_rwlock_wrlock(&rwl);	
			nr2+=1;
			pthread_rwlock_unlock(&rwl);
		}
	}
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t t[7];
	pthread_rwlock_init(&rwl, NULL);
	pthread_mutex_init(&mtx, NULL);		

	for(int i=0;i<7;i++)
		pthread_create(&t[i], NULL, f, NULL);
	
	for(int i=0;i<7;i++)
		pthread_join(t[i], NULL);

	pthread_rwlock_destroy(&rwl);
	pthread_mutex_destroy(&mtx);
	printf("Nr1: %d\nNr2: %d\n", nr1, nr2);
		
	return 0;
}
