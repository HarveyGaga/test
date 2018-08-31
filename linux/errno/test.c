/*************************************************************************
	> File Name: test.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年05月16日 星期二 13时30分37秒
 ************************************************************************/

#include<stdio.h>
#include<errno.h>

int main(void)
{
	printf("EINTR = %d\n", EINTR);
	printf("EWOULDBLOCK = %d\n", EWOULDBLOCK);
	return 0;
}
