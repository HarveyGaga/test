/*************************************************************************
	> File Name: main.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年03月21日 星期三 13时58分31秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<mcheck.h>

int main()  
{  
	setenv("MALLOC_TRACE", "taoge.log", 1);  
	mtrace();  

	int *p = (int *)malloc(2 * sizeof(int));  
							  
	return 0;  
}
