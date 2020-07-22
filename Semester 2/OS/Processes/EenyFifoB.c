#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Process B
int main(int argc, char** argv)
{
        int a2b, b2a, n;
        a2b = open("a2b", O_RDONLY);
        b2a = open("b2a", O_WRONLY);

        while(1)
        {
                if(read(a2b, &n, sizeof(int)) < 0)
                {
			printf("Failed to read\n");
			break;
                }
		if(n<=0)
                        break;
                n -= 1;
                printf("B --> %d\n", n);
                if(write(b2a, &n, sizeof(int)) < 0)
                        break;
        }
        close(a2b); close(b2a);

        return 0;
}
