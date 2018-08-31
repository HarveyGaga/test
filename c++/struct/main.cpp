/*************************************************************************
	> File Name: main.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年12月19日 星期二 15时11分20秒
 ************************************************************************/

#include<iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

typedef struct __Config {
	char name[20];
}Config;

void print(char *buf, size_t size) {
	for(size_t i = 0; i < size; i++) {
		printf("%02x ", buf[i]);
	}
	printf("\n");
}

int main(void) {
	Config con1;
	Config con2;

	print(con1.name, sizeof(con1.name));
	print(con2.name, sizeof(con2.name));
	con2 = con1;
	print(con1.name, sizeof(con1.name));
	print(con2.name, sizeof(con2.name));

	return 0;
}
