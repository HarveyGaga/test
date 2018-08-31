/*************************************************************************
	> File Name: test.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年07月27日 星期四 15时13分34秒
 ************************************************************************/
#include <iostream>

using namespace std;

class B
{
public:
	B(void)
	{
		cout << "B(void)" << endl;
		a = 1;
	}

#if 0
	void foo(int data)
	{
		cout << "no const" << endl;
		a = data;
	}
#else

	void foo(int data) const
	{
		cout << "const" << endl;
		//a = data;
	}
#endif

	int a;
};

int main(void)
{
	B b1;
	b1.foo(1);
	
	const B b2;
	b2.foo(2);

	return 0;
}
