#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
int n, m=-1, ap=-1;
int* v;
pthread_mutex_t mtx;

void* reader(void*a)
{
	printf("Give n: ");
	scanf("%d", &n);
	int i;
	v = (int*)malloc(sizeof(int)*n);
	int fd = open("matrix.bin", O_RDONLY);
	for(i=0;i<n;i+=1)
		if(read(fd, &v[i], sizeof(char))<0)
			perror("Error on read");


	return NULL;
}

void* f(void* a)
{
	int x = rand()%256;
	int i, aparitii=0;
	for(i=0;i<n;i+=1)
		if(v[i] == x)
			aparitii+=1;

	printf("M local: %3d Ap local: %3d\n",x, aparitii);
	
	pthread_mutex_lock(&mtx);
	if(ap < aparitii)
	{
		m = x;
		ap = aparitii;
	}
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

	if(pthread_mutex_init(&mtx, NULL)!=0)
		perror("Error on mtx init");
	
	pthread_t t[20];
	
	int i;
	for(i=0;i<20;i+=1)
		if(pthread_create(&t[i], NULL, f, NULL)!=0)
			perror("Error on create");
	for(i=0;i<20;i+=1)
		if(pthread_join(t[i], NULL)!=0)
			perror("Error on join");
	if(pthread_mutex_destroy(&mtx)!=0)
		perror("Error on destroy");
	
	printf("M: %d Ap: %d\n",m, ap);
	free(v);
	return 0;
}
