/*************************************************************************
	> File Name: test.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年08月07日 星期一 16时45分29秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

void signal_handler(int signum)
{
	printf("catch signal %d\n", signum);

	if(signum == 2)
	{
		exit(0);
	}
}

int main(void)
{
	int i;
	sighandler_t ret;

	printf("SIGRTMIN = %d\n", SIGRTMIN);
	printf("SIGRTMAX = %d\n", SIGRTMAX);
	printf("signal_handler = %x\n", signal_handler);

	for(i = 1; i < SIGRTMAX; i++)
	{
		ret = signal(i, signal_handler);
		printf("%d = %d\n", i, ret);
	}

	while(1)
	{
		sleep(1);
	}

	return 0;
}
