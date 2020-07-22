/*
10. Write a program that receives strings of alphanumeric characters as command line arguments (validation is not required). For each string the program creates a thread which calculates the number of digits, the number of consonants and the number of vowels. The thread adds the results to three global variables, one for digits, one for vowels and one for consonants. The main program prints the end results (total number of digits, vowels and consonants across all the received command line arguments) and terminates. Use efficient synchronization.

*/

#include <pthread.h>
#include <stdio.h>
#include <string.h>

int d=0,v=0,c=0;
pthread_mutex_t md,mv,mc;

void* f(void* a)
{	
	char* s= (char*)a;
	int digits=0, vowels=0, consonants=0;	
	for(int i=0;i<strlen(s);i++)
	{
		if(strchr("0123456789", s[i]))
			digits+=1;
		else if(strchr("aeiouAEIOU", s[i]))
			vowels+=1;
		else
			consonants+=1;
	}
	pthread_mutex_lock(&md);
	d += digits;
	pthread_mutex_unlock(&md);
	pthread_mutex_lock(&mv);
	v+=vowels;
	pthread_mutex_unlock(&mv);
	pthread_mutex_lock(&mc);
	c+=consonants;
	pthread_mutex_unlock(&mc);
	
	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t t[argc-1];
	pthread_mutex_init(&md, NULL);
	pthread_mutex_init(&mv, NULL);
	pthread_mutex_init(&mc, NULL);
	for(int i=0;i<argc-1;i++)
		pthread_create(&t[i], NULL, f, argv[i+1]);
	for(int i=0;i<argc-1;i++)
		pthread_join(t[i], NULL);
	printf("Digits: %d\nVowels: %d\nConsonants: %d\n", d ,v,c);

	return 0;
}


