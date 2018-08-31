/*************************************************************************
	> File Name: swap.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年07月25日 星期二 16时02分41秒
 ************************************************************************/

#include<iostream>
using namespace std;

void swap(int& a, int& b)
{
	int c = a;

	cout << &a << endl;
	a = b;
	b = c;
}

int main(void)
{
	int a = 100, b = 200;

	cout << &a << endl;
	cout << a << ", " << b << endl;

	swap(a, b);

	cout << a << ", " << b << endl;

	return 0;
}
