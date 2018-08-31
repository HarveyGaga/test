/*************************************************************************
	> File Name: main.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年12月26日 星期二 09时57分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

int main(void) {
	char *p = (char*)malloc(1024);
	printf("p =  0x%016x\n", p);
	printf("&p = 0x%016x\n", &p);
	free(p);
	free(p);

	return 0;
}
