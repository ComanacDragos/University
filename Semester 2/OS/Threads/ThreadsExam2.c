#include <pthread.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char lit[5]="abcde";
int frecvCuvinte[5], frecvLitere[5];
char** cuvinte;

pthread_mutex_t mtxCuv[5], mtxLit[5];

void* f(void*a)
{
	char* s = (char*)a;
	int i,frecvL[5]={0,0,0,0,0};
	for(i=0;i<strlen(s);i+=1)
	{
		int j;
		for(j=0;j<5;j+=1)
			if(s[i] == lit[j])
			{
				frecvL[j]+=1;
				break;
			}
	}
	

	for(i=0;i<5;i+=1)
		if(frecvL[i]!=0)
		{
			pthread_mutex_lock(&mtxLit[i]);
			frecvLitere[i] += frecvL[i];
			pthread_mutex_unlock(&mtxLit[i]);
			
			pthread_mutex_lock(&mtxCuv[i]);
			strcat(cuvinte[i], s);
			strcat(cuvinte[i], " ");
			frecvCuvinte[i] += 1;
			pthread_mutex_unlock(&mtxCuv[i]);	
		}
	return NULL;
}

int main(int argc, char** argv)
{
	if(argc == 1)
	{	
		printf("Give arguments\n");
		exit(1);
	}
	pthread_t t[argc-1];
	cuvinte = (char**)malloc(sizeof(char*)*5);	
	int i;
	for(i=0;i<5;i+=1)
	{
		if(pthread_mutex_init(&mtxCuv[i],NULL)!=0)
			perror("Error on mutex init");
		if(pthread_mutex_init(&mtxLit[i],NULL)!=0)
			perror("Error on mutex init");		

		cuvinte[i] = (char*)malloc(sizeof(char)*256);
	}
	for(i=0;i<argc-1;i+=1)
		if(pthread_create(&t[i], NULL,f,argv[i+1])!=0)
			perror("Error on create");

	for(i=0;i<argc-1;i+=1)
		if(pthread_join(t[i], NULL)!=0)
			perror("Error on join");
	
	for(i=0;i<5;i+=1)
	{
		printf("%c: Aparitii: %d NrCuvinte: %d\nCuvinte: %s\n\n", lit[i], frecvLitere[i], frecvCuvinte[i], cuvinte[i]);
	}

	for(i=0;i<5;i+=1)
	{
		if(pthread_mutex_destroy(&mtxCuv[i])!=0)
			perror("Error on destroy");
		if(pthread_mutex_destroy(&mtxLit[i])!=0)
			perror("Error on destroy");
		free(cuvinte[i]);
	}
	free(cuvinte);		

	return 0;
}
