#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	int i;

    printf("%d\n", atoi("NULL"));
    printf("%d\n", atoi("28"));
    printf("%d\n", atoi("0"));


	for(i = 0; i < 100; i++)
	{
		printf("i = %d\n", i);
		sleep(1);
	}

    return 0;
}
