#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
int nr_files=0, nr_folders=0;

pthread_mutex_t mtf, mtd;

void* f(void* a)
{
	return NULL;
}

int main(int argc, char** argv)
{
	if(argc==1)
	{
		printf("Give arguments\n");
		exit(1);
	}
	int i;
	for(i=1;i<argc;i++)
	{
		char s[100] = "if [ -f \"";
		strcat(s,argv[i]);
		strcat(s,"\" ];then echo 0;else echo 1;fi");
	
		FILE* fd = popen(s, "r");
		int x;
		fscanf(fd, "%d", &x);
		pclose(fd);
		if(x == 1)
			printf("%s is a directory\n", argv[i]);
		else
			printf("%s is a file\n", argv[i]);
	}

	return 0;
}
