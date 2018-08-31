/*************************************************************************
	> File Name: main.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年02月27日 星期二 10时25分41秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
using namespace std;


class A {
public:
	static int c;
	int a;
	char b;
	double d;

	void func1(void) {
	}

	static void func2(void) {
		func1();
	}
};

int A::c = 1;

int main(void) {
	A a;
	printf("sizeof(A) = %lu\n", sizeof(A));
	printf("&A.a = 0x%x\n", &a.a); 
	printf("&A.b = 0x%x\n", &a.b); 
	printf("&A.c = 0x%x\n", &a.c); 
	printf("&A.d = 0x%x\n", &a.d); 

	return 0;
}
