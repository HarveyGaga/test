/*************************************************************************
	> File Name: test.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年07月25日 星期二 15时50分10秒
 ************************************************************************/

#include<iostream>
using namespace std;

int main(int argc, char *argv[])
{
	int a = 10;
	int& b = a;
	//int& b; //引用必须被初始化

	cout << b << endl;

	return 0;
}
