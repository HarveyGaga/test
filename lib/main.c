/*************************************************************************
	> File Name: main.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年07月04日 星期二 11时27分19秒
 ************************************************************************/

#include<stdio.h>
#include<unistd.h>

extern int add(int a, int b);


int main(void)
{
	int ex = 5;
	while(1){
		printf("1+2 = %d\n", add(1, 2));
		sleep(1);
	}
	return 0;
}
