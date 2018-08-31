/*************************************************************************
	> File Name: erase.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年08月30日 星期四 14时26分02秒
 ************************************************************************/

#include<iostream>
#include<list>
using namespace std;

int main(int argc, char **argv) {
	list<int> lst;

	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(4);
	lst.push_back(5);
	lst.push_back(6);
	lst.push_back(7);

	for (list<int>::iterator it = lst.begin(); it != lst.end();) {
		if (*it == 3) {
			it = lst.erase(it);
			continue;
		}
		cout << *it << " "; 
		++it;
	}
	cout << endl;

	return 0;
}
