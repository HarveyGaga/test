/*************************************************************************
	> File Name: strncpy.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年09月06日 星期三 11时34分55秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main(void)
{
	char buffer[9];
	char *name = "1234567890abcdefghijk";
	int i;

	for(i = 0; i < sizeof(buffer); i++)
		printf("%x ", buffer[i]);
	printf("\n");

	strncpy(buffer, name, sizeof(buffer));

	for(i = 0; i < sizeof(buffer); i++)
		printf("%x ", buffer[i]);
	printf("\n");

	printf("%s\n", buffer);
	for(i = 0; ; i++){
		printf("%x ", buffer[i]);
		if(buffer[i] == 0)
			break;
	}

	printf("\n");

	return 0;
}
