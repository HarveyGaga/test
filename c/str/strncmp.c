
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
	char buf1[32];
	char buf2[32];

	strcpy(buf1, "京A00000");
	strcpy(buf2, "京A00000");

	res = strncmp(buf1, buf2, sizeof(buf1));
	printf("res = %d\n", res);
	return 0;
}
