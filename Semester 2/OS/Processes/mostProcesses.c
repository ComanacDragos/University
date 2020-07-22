#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	FILE* fp;
	fp=popen("ps -ef | tail -n +2 | awk '{print $1}' | sort | uniq -c | head -1", "r");
	char *s = (char*)malloc(sizeof(char)*200);
	int n;
	fscanf(fp, "%d %s\n", &n, s);
	printf("%d %s",n, s);
	//printf("%d %s",n,s);
	pclose(fp);
	return 0;
}
