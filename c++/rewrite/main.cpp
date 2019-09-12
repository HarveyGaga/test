/*************************************************************************
	> File Name: main.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年11月06日 星期二 20时10分53秒
 ************************************************************************/

#include<iostream>
using namespace std;

class AA
{
public:
    virtual void print(int x )
    {
        cout << "父类:" << x  << endl;
    }
};

class BB : public AA
{
public:
    virtual void print(int x)
    {
        cout << "子类:" << x  << endl;
    }
};

int main()
{
    AA *p = NULL;
    BB b; 
    p = &b;
    //p->print(1);
    b.print(1);
}

