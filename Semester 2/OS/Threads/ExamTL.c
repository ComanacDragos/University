#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int min=1000, MAX;
int* TOTALMAX;
int fd;
int size=0;

pthread_mutex_t mtxMIN, mtxRead;
pthread_barrier_t barrier;

void* f(void*a)
{
	int start,i;
	
	pthread_mutex_lock(&mtxRead);
	start = size;
	size+=200;
	for(i=start;i<start+200;i+=1)
		if(read(fd, &TOTALMAX[i],sizeof(char))<0) 
				perror("Error on read");
	pthread_mutex_unlock(&mtxRead);

	pthread_barrier_wait(&barrier);

	int N=rand()%256;
	int k =rand()%50+50;
	int s=0;
	for(i=start;i<start+200;i+=1)
		s+= TOTALMAX[i];
	int dif = abs(N-s/k);
	printf("%4d %4d K: %4d N: %4d S: %4d DIF: %4d\n", start, start+200, k,N,s,dif);
	pthread_mutex_lock(&mtxMIN);
	if(min>dif)
		min=dif;
	pthread_mutex_unlock(&mtxMIN);
	return NULL;
}

int main(int argc, char** argv)
{
	min = 1000;
	size=0;
	srand(time(0));
	printf("Give max: ");
	scanf("%d",&MAX);
	int nrThreads = MAX/200;
	
	if(pthread_mutex_init(&mtxMIN,NULL)!=0)
		perror("Error on init");

	if(pthread_mutex_init(&mtxRead,NULL)!=0)
		perror("Error on init");
	
	if(pthread_barrier_init(&barrier,NULL, nrThreads)!=0)
		perror("Error on init");

	pthread_t t[nrThreads];
	int i;	
	fd = open("matrix.bin", O_RDONLY);
	TOTALMAX=(int*)malloc(sizeof(int)*MAX);
	/*for(i=0;i<MAX;i+=1)
	{
		if(read(fd, &TOTALMAX[i], sizeof(char))<0)
			perror("Error on read");
	}*/
	//int starts[nrThreads];
	for(i=0;i<nrThreads;i+=1)
	{	
		//starts[i]=i*200;
		if(pthread_create(&t[i], NULL,f, NULL)!=0)
			perror("Error on create");
	}
	for(i=0;i<nrThreads;i+=1)
		if(pthread_join(t[i],NULL)!=0)
			perror("Error on join");

	
	if(pthread_mutex_destroy(&mtxMIN)!=0)
		perror("Error on mutex destroy");
	if(pthread_mutex_destroy(&mtxRead)!=0)
		perror("Error on mutex destroy");

	if(pthread_barrier_destroy(&barrier)!=0)
		perror("Erro on desttroy");
	
	close(fd);
	free(TOTALMAX);
	printf("MIN dif: %d\nReads: %d\n",min, size);
	return 0;

}
