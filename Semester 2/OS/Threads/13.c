/*
13. Write a C program that reads a number N and creates 2 threads. One of the threads will generate an even number and will append it to an array that is passed as a parameter to the thread. The other thread will do the same, but using odd numbers. Implement a synchronization between the two threads so that they alternate in appending numbers to the array, until they reach the maximum length N.

*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

int n;
pthread_mutex_t mtx1, mtx2;

void print_array(int len, int* arr)
{
	int i;
	printf("Len: %d ", len);
	for(i=0;i<len;i+=1)
		printf("%d ", arr[i]);
	printf("\n\n");
}

void* even(void* a)
{
	int* evens = (int*)a;
	int i;

	for(i=0;i<n;i++)
	{
		int x = rand()%1000;
		x += x%2;
		pthread_mutex_lock(&mtx1);
		evens[i] = x;
		print_array(i+1, evens);
		pthread_mutex_unlock(&mtx2);
	}

	return NULL;
}

void* odd(void* a)
{
	int* odds = (int*)a;
	int i;
	for(i=0;i<n;i++)
	{
		int x = rand()%1000;
		x += x%2 + 1;
		pthread_mutex_lock(&mtx2);
		odds[i] = x;
		print_array(i+1, odds);
		pthread_mutex_unlock(&mtx1);
	}

	return NULL;
}

int main(int argc, char** argv)
{
	srand(time(0));
	printf("Give N: ");
	scanf("%d", &n);
	int* odds = (int*)malloc(sizeof(int)*n);
	int* evens = (int*)malloc(sizeof(int)*n);
	
	if(pthread_mutex_init(&mtx1, NULL)!=0)
		perror("Error on mutex init");
	if(pthread_mutex_init(&mtx2, NULL)!=0)
		perror("Error on second mutex init");
	
	pthread_t t[2];
	if(pthread_create(&t[0], NULL, even, evens)!=0)
		perror("Error on create");
	if(pthread_create(&t[1], NULL, odd, odds)!=0)
		perror("Error on create");

	int i;
	for(i=0;i<2;i+=1)
		if(pthread_join(t[i], NULL)!=0)
			perror("Error on join");

	free(odds);
	free(evens);
	return 0;	
}
