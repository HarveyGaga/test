/*************************************************************************
	> File Name: template.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年05月23日 星期三 15时30分53秒
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

template <typename T> T max(T &a, T &b) {
	return a > b? a : b;
}

int min(int a, int b) {
	return a < b? a : b;
}

int main() {
	cout << max(1,2) << endl;
	cout << min(1,2) << endl;
	cout << max(1.1,2.2) << endl;
	cout << max(string("123"), string("456")) << endl;
	return 0;
}
