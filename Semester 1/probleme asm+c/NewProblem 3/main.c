#include <stdio.h>

int str_len(char v[]);
int get_base_ten(char v[], int n);
int conc(char v1[], int n, char v2[], int n2);
int strcpy(char dest[], char source[]);

int main()
{
	char v[101], v2[101] ;
	gets(v);
	gets(v2);

	int n = str_len(v), m = str_len(v2);

	strcpy(v, get_base_ten(v, n));
	strcpy(v2, get_base_ten(v2, m));
	n = str_len(v);
	m = str_len(v2);

	printf("%s\n", conc(v,n,v2,m));
	printf("%s", conc(v2, m, v, n));

	return 0;
}	
