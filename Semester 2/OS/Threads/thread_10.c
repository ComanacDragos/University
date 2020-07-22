/*
10. Write a program that receives strings of alphanumeric characters
 as command line arguments (validation is not required).
 For each string the program creates a thread which calculates the number of digits,
 the number of consonants and the number of vowels.
 The thread adds the results to three global variables,
 one for digits, one for vowels and one for consonants.
 The main program prints the end results
 (total number of digits, vowels and consonants across all the received command line arguments) and terminates.
 Use efficient synchronization.

*/

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

int digits=0, vowels=0, consonants=0;
pthread_mutex_t m_d, m_v, m_c;

void* f(void *a)
{
	char* s = (char*)a;
	for(int i=0;i<strlen(s);i++)
	{
		if(strchr("0123456789", s[i]))
		{
			pthread_mutex_lock(&m_d);
			digits+=1;
			pthread_mutex_unlock(&m_d);
		}
		else if(strchr("aeiou", s[i]))
		{
			pthread_mutex_lock(&m_v);
			vowels+=1;
			pthread_mutex_unlock(&m_v);
		}
		else
		{
			pthread_mutex_lock(&m_c);
			consonants+=1;
			pthread_mutex_unlock(&m_c);
		}
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
	for(int i=1;i<argc;i++)
	{
		pthread_create(&t[i], NULL, f, argv[i]);
	}	

	for(int i=1;i<argc;i++)
		pthread_join(t[i], NULL);
		
	printf("Digits: %d\nVowels: %d\nConsonants: %d\n", digits, vowels, consonants);
	pthread_mutex_destroy(&m_d);
	pthread_mutex_destroy(&m_v);
	pthread_mutex_destroy(&m_c);
	return 0;
}
