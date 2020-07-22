/*
12. Write a C program that receives integers as command line argument. The program will keep a frequency vector for all digits. The program will create a thread for each argument that counts the number of occurences of each digit and adds the result to the global frequency vector. Use efficient synchronization.

*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int freq[10];
pthread_mutex_t mtx[10];

void* f(void* a)
{
	int f[10];
	for(int i=0;i<10;i++)
		f[i] = 0;
	int n = atoi((char*)a);
	if(n==0)
		f[0] += 1;
	while(n)
	{
		f[n%10] += 1;
		n/=10;
	}
	for(int i=0;i<10;i++)
	{
		if(f[i] != 0)
		{
			pthread_mutex_lock(&mtx[i]);
			freq[i] += f[i];
			pthread_mutex_unlock(&mtx[i]);
		}
	}
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t t[argc-1];
	for(int i=0;i<10;i++)
		pthread_mutex_init(&mtx[i],NULL);
	for(int i=0;i<argc-1;i++)
		pthread_create(&t[i], NULL, f, argv[i+1]);

	for(int i=0;i<argc-1;i++)
		pthread_join(t[i], NULL);

	for(int i=0;i<10;i++)
	{
		printf("%d ", freq[i]);
		pthread_mutex_destroy(&mtx[i]);
	}
	return 0;

}

