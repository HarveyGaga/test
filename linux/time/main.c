/*************************************************************************
	> File Name: main.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年06月06日 星期三 15时56分20秒
 ************************************************************************/

#include<stdio.h>
#include <time.h>

int main() {
	time_t t;

	t = time(NULL);
	printf("%ld\n", t);

	return 0;
}

