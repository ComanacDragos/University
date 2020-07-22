#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int n=1, arr[50], size=0;
pthread_mutex_t mtxarr;
pthread_mutex_t mtxn;

void* f(void*a)
{
	while(1)
	{
		int aux;
		pthread_mutex_lock(&mtxn);
		if(n==56)
			break;
		aux=n;
		n+=1;
		pthread_mutex_unlock(&mtxn);
		if(aux%2 == 0 || aux%10 == 2 || aux/10 == 2)
		{
			pthread_mutex_lock(&mtxarr);
			arr[size] = aux;
			size+=1;
			pthread_mutex_unlock(&mtxarr);
		}
		else
		{
			printf("%d\n", aux);
		}
	}
	pthread_mutex_unlock(&mtxn);
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t t[10];
	
	if(pthread_mutex_init(&mtxarr, NULL)!=0)
		perror("Error on mtx init");
	if(pthread_mutex_init(&mtxn, NULL)!=0)
		perror("Error on rwl init");

	int i;
	for(i=0;i<10;i+=1)
		if(pthread_create(&t[i], NULL,f,NULL)!=0)
			perror("Error on create");
	for(i=0;i<10;i+=1)
		if(pthread_join(t[i], NULL)!=0)
			perror("Error on join");
	
	if(pthread_mutex_destroy(&mtxarr)!=0)
		perror("Error on destroy");
	if(pthread_mutex_destroy(&mtxn)!=0)
		perror("Error on destroy");
	for(i=0;i<size;i+=1)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}




