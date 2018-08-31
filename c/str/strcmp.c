
/*************************************************************************
	> File Name: strcmp.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年08月21日 星期一 10时27分44秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>

int main(void)
{
	int res;
	char *s1 = "192.168.1.171";
	char *s2 = "192.168.1.172";

	res = strcmp(s1, s2);
	printf("res = %d\n", res);
	return 0;
}
