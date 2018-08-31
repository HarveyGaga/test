/*************************************************************************
	> File Name: test.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年08月17日 星期四 10时40分21秒
 ************************************************************************/

#include<iostream>
using namespace std;

class A
{
public:
	int a;
	static double d;
	A()
	{
		cout << "A()" << endl;
	}

	~A()
	{
		cout << "~A()" << endl;
	}
};

int main(void)
{
	A *pa = new A;

	cout << "sizeof(A) = " << sizeof(A) << endl;
	delete pa;
	return 0;
}
