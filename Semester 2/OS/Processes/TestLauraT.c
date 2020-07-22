#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

pthread_mutex_t mtx;
int min = (unsigned)-1>>1;

typedef struct Node{
	int* v, s;
}Node;

void* f (void* a)
{
	Node str = *(Node*)a;
	int start = str.s;
	int* v = str.v;
	int end = start + 100;
	int current, minP = -1;
	int i=start;
	while(v[i] % 7 != 0 && i<end)
		i+=1;
	
	current = v[i];
	while(v[i]%7!=0)
		i+=1;
	minP = current*v[i];
	current = v[i];
	for(int j=i;j<end;j++)
	{
		if(v[j] %7==0)
		{
			if(minP > v[j]*current)
			{
				minP = v[j]*current;
				current = v[j];
			}						
		}
	}
	pthread_mutex_lock(&mtx);
	if(min > minP)
		min = minP;
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

int main(int argc, char** argv)
{
	int v[2000];
	printf("%d\n", min);
	int fd = open("matrix.bin", O_RDONLY);
	
	for(int i=0;i<2000;i++)
	{
		read(fd, &v[i], sizeof(int));
	}
	pthread_t t[20];
	pthread_mutex_init(&mtx, NULL);
	Node str[20];
	for(int i=0;i<20;i++)
	{
		str[i].v = v;
		str[i].s = i*100;
		pthread_create(&t[i], NULL, f, &str[i]);
	}

	for(int i=0;i<20;i++)
		pthread_join(t[i],NULL);
	close(fd);
	pthread_mutex_destroy(&mtx);
	printf("%d\n", min);
}



