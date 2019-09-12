/*************************************************************************
	> File Name: strlen.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年09月06日 星期三 11时41分16秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

void* fun(void *param) {
	return NULL;
}

int main(int argc, char *argv[])
{
	char *str = "barCode=&rodCode=&parkCode=ZOOM CAMERA&uploadTime=20170906170745&berthNumber=&imageType=1&busiType=2&dataSource=10&noncestr=&zkey=zhihuihutong";

	printf("%lu\n", strlen(str));

	int *pi = (int*)malloc(1024);
	free(pi);

	pthread_t tid;
	pthread_create(&tid, NULL, fun, NULL);
	pthread_join(tid, NULL);

	return 0;
}
