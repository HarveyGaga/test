/*************************************************************************
	> File Name: test.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年07月25日 星期二 20时15分04秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
using namespace std;

class Animal
{
public:
	void who(void) {
	}
private:
	int age;
	char name[4];
};


class Dog : public Animal
{
public:
	/* 父类的who被隐藏 */
	void who(int a) {
	}
public:
	int kind;
	char ch;
};

int main(void)
{
	Animal a;
	Dog d;

	d.who();

	return 0;
}
