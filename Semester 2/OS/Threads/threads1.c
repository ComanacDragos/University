#include <stdio.h>
#include <pthread.h>

int n=0;
pthread_mutex_t m;

void* f (void* a)
{
	printf("Thread: %d\n", *(int*)a);
	for(int i=0;i<1000*1000;i++)
	{
		pthread_mutex_lock(&m);
		n += 1;
		pthread_mutex_unlock(&m);
	}
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t t[10];
	int ids[10];
	pthread_mutex_init(&m, NULL);	
	for(int i=0;i<10;i++)
	{
		ids[i] = i;
		pthread_create(&t[i], NULL, f, &ids[i]); 
	}

	for(int i=0;i<10;i++)
		pthread_join(t[i], NULL);
	printf("%d\n", n);
	pthread_mutex_destroy(&m);
	return 0;
}
