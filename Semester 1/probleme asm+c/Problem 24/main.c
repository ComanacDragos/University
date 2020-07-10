#include <stdio.h>

int array_max(int v[], int n);

int main()
{
	int v[101], n, i, *fptr, mx;
	scanf("%d", &n);
	for (int i = 0; i < n; i += 1)
		scanf("%d", &v[i]);

	fptr = fopen("file.txt", "w");

	
	mx = array_max(v, n);
	
	fprintf(fptr, "%d\n", mx);
	
	fclose(fptr);
	return 0;
} 