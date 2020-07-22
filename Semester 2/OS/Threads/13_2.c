#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int n;
pthread_mutex_t mtx1, mtx2;	

void* even(void*a)
{
	
	return NULL;
}

void* odd(void*a)
{
	return NULL;
}


int main(int argc, char** argv)
{
	srand(time(0));
	printf("Give n: ");
	scanf("%d", &n);
	
	pthread_t t1,t2;
	int odds[n], evens[n];
	if(pthread_mutex_init(&mtx1, NULL)!=0)
		perror("Error on init");
	if(pthread_mutex_init(&mtx2, NULL)!=0)
		perror("Error on init");


	if(pthread_create(&t1, NULL, even, evens)!=0)
		perror("Error on create");
	if(pthread_create(&t2, NULL, odd, odds)!=0)
		perror("Error on create");
	
	if(pthread_join(t1, NULL)!=0)
		perror("Error on join");
	if(pthread_join(t2, NULL)!=0)
		perror("Error on join");
	if(pthread_mutex_destroy(&mtx1)!=0)
		perror("Error on destroy");
	if(pthread_mutex_destroy(&mtx2)!=0)
		perror("Error on destroy");
	
	return 0;
}
