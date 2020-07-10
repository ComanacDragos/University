#include <stdio.h>

int interleave(char v1[], char v2[], int n);

int f(char v1)
{
	printf("%s \n", v1);

}

int main() 
{
	int n;
	char v1[101], v2[101];


	//printf("Give n: ");
	scanf("%d ", &n);

	//printf("\nGive first array:\n");
	gets(v1);

	//printf("\nGive second array:\n");
	gets(v2);
	
	printf("The two result strings are: \n%s \n", interleave(v1, v2, n));
	printf("%s\n", interleave(v2, v1, n));


	return 0;
}