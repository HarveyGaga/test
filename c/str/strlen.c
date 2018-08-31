/*************************************************************************
	> File Name: strlen.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年09月06日 星期三 11时41分16秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>


int main(int argc, char *argv[])
{
	char *str = "barCode=&rodCode=&parkCode=ZOOM CAMERA&uploadTime=20170906170745&berthNumber=&imageType=1&busiType=2&dataSource=10&noncestr=&zkey=zhihuihutong";

	if(argc != 2)
	{
		return -1;
	}

	printf("%d\n", strlen(argv[1]));

	return 0;
}
