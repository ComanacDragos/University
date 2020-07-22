#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int* v;
int n, maxSum = -1;
pthread_mutex_t mtx;
typedef struct Index{
	int start,end;
}Index;

void* reader(void*a)
{
	printf("Give n: ");
	scanf("%d", &n);
	
	v = (int*)malloc(sizeof(int)*n);
	int i;
	for(i=0;i<n;i+=1)
		v[i] = rand()%255+1;
	return NULL;
}

void* f(void* a)
{
	Index idx = *(Index*)a;
	int c=0,i;
	int localSum=(unsigned)-1>>1, currentMultiple;
	for(i=idx.start;i<idx.end;i+=1)
	{
		if(v[i]%7==0)
		{
			if(c==0)
			{
				c+=1;
				currentMultiple = v[i];
			}
			else
			{
				if(v[i]+currentMultiple < localSum)
					localSum = v[i] + currentMultiple;
				currentMultiple = v[i];
				c+=1;
			}
		}
	}
	if(c<=1)
		localSum = -1;
	printf("Start: %4d End: %4d Sum: %4d\n",idx.start, idx.end, localSum);
	pthread_mutex_lock(&mtx);
	if(localSum > maxSum)
		maxSum = localSum;
	pthread_mutex_unlock(&mtx);

	return NULL;
}

int main(int argc, char** argv)
{
	srand(time(0));
	pthread_t r;
	if(pthread_create(&r, NULL, reader, NULL)!=0)
		perror("Error on create");
	if(pthread_join(r, NULL)!=0)
		perror("Error on join");
	
	int threads=n/200;
	pthread_t t[threads], last;
	int i;

	if(pthread_mutex_init(&mtx, NULL)!=0)
		perror("Error on init");

	Index indexi[threads], index;
	for(i=0;i<threads;i+=1)
	{
		indexi[i].start = i*200;
		indexi[i].end = i*200 + 200;
		if(pthread_create(&t[i], NULL, f, &indexi[i])!=0)
			perror("Error on create");
	}
	if(n%200!=0)
	{
		index.start = n-n%200;
		index.end = n;
		if(pthread_create(&last, NULL, f, &index)!=0)
			perror("Error on create");
	}
	
	for(i=0;i<threads;i+=1)
		if(pthread_join(t[i], NULL)!=0)
			perror("Error on join");

	if(n%200!=0)
		if(pthread_join(last, NULL)!= 0)
			perror("Error on join");

	if(pthread_mutex_destroy(&mtx)!=0)
		perror("Error on destroy");
	free(v);
	printf("End sum: %d\n", maxSum);
	return 0;
}
