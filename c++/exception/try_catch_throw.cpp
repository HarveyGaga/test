/*************************************************************************
	> File Name: try_catch_throw.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年05月22日 星期二 11时41分32秒
 ************************************************************************/

#include <iostream>
using namespace std;
 
double division(int a, int b)
{
   if( b == 0 )
   {
      throw "Division by zero condition!";
   }
   return (a/b);
}
 
int main ()
{
   int x = 50;
   int y = 0;
   double z = 0;
 
   try {
     z = division(x, y);
     cout << z << endl;
   }catch (...) {
     //cerr << msg << endl;
   }
 
   return 0;
}

