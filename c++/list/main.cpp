/*************************************************************************
	> File Name: main.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年03月09日 星期五 11时38分51秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<list>
using namespace std;

int main(void) {
	list<int> l;
	while(1) {
		int in;
		scanf("%d", &in);

		list<int>::iterator it;
		for(it = l.begin(); it != l.end(); it++) {
			if(*it >= in)
				break;
		}
		l.insert(it, in);
		for(it = l.begin(); it != l.end(); it++) {
			printf("%d ", *it);
		}
		printf("\n");
	}

	return 0;
}
