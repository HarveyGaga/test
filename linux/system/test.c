/*************************************************************************
	> File Name: test.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年05月22日 星期一 16时04分52秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main(int argc, char *argv[])
{
	int ret;

	ret = system(argv[1]);
	printf("ret = %d\n", ret);
	if(ret < 0)
	{
		return -1;
	}

	if(WIFEXITED(ret))
	{
		printf("normal termination, exit status = %d\n", WEXITSTATUS(ret));
	}
	else if(WIFSIGNALED(ret))
	{
		printf("abnormal termination,signal number =%d\n", WTERMSIG(ret));
	}
	else if(WIFSTOPPED(ret))
	{
		printf("process stopped, signal number =%d\n", WSTOPSIG(ret));
	}
	return 0;
}
