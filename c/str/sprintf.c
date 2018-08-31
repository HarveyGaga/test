/*************************************************************************
	> File Name: sprintf.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年07月06日 星期四 11时34分04秒
 ************************************************************************/

#include<stdio.h>

int main(void)
{
	int i;
	char buffer[10];

	i = 101;
	sprintf(buffer, "%05d\n", i);
	printf("%s\n", buffer);

	return 0;
}
