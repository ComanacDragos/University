#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

int n;
pthread_cond_t c;
pthread_mutex_t mtx;
void print_array(int len, int* arr)
{
        int i;
        printf("Len: %2d ", len);
        for(i=0;i<len;i+=1)
                printf("%4d ", arr[i]);
        printf("\n\n");
}

void* odd(void* a)
{
	int* odds = (int*)a;
	int i;
	for(i=0;i<n;i+=1)
	{
		int x = rand()%1000;
		x+= x%2+1;
		odds[i] = x;
		print_array(i+1, odds);
		pthread_cond_signal(&c);
		pthread_mutex_lock(&mtx);
		pthread_cond_wait(&c, &mtx);
		pthread_mutex_unlock(&mtx);
	}
	pthread_cond_signal(&c);
	return NULL;
}

void* even(void* a)
{
	int* evens = (int*)a;
	int i;
	for(i=0;i<n;i+=1)
	{
		int x = rand()%1000;
		x+= x%2;
		evens[i] = x;
		print_array(i+1, evens);
		pthread_cond_signal(&c);
		pthread_mutex_lock(&mtx);
		pthread_cond_wait(&c, &mtx);
		pthread_mutex_unlock(&mtx);
	}
	pthread_cond_signal(&c);
	return NULL;
}

int main(int argc, char** argv)
{
	srand(time(0));
	printf("Give n: ");
	scanf("%d", &n);
	int* odds = (int*)malloc(sizeof(int)*n);
	int* evens = (int*)malloc(sizeof(int)*n);
	
	if(pthread_mutex_init(&mtx, NULL)!=0)
		perror("Error on mtx init");
	if(pthread_cond_init(&c,NULL)!=0)
		perror("Error on mtx init");

	pthread_t t1,t2;
	if(pthread_create(&t1, NULL, odd, odds)!=0)
		perror("error on create");
	if(pthread_create(&t2, NULL, even, evens)!=0)
		perror("Error on create");
	

	if(pthread_join(t1, NULL)!=0)
		perror("Error on join");
	if(pthread_join(t2, NULL)!=0)
		perror("Error on join");
	if(pthread_mutex_destroy(&mtx)!=0)
		perror("Error on destroy");
	if(pthread_cond_destroy(&c)!=0)
		perror("Error on destroy");

	free(odds);
	free(evens);
	return 0;
}
