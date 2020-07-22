#include <stdio.h>
#include <pthread.h>

void* f (void* a)
{
	printf("Thread: %d\n", *a);
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t t[10];
	int i, ids[10];
	
	for(int i=0;i<10;i++)
	{
		ids[i] = i;
		pthread_create(&t[i], NULL, f, &i); 
	}

	for(int i=0;i<10;i++)
		pthread_join(t[i], NULL);
	return 0;
}
