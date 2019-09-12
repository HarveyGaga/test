#include <iostream>
#include <string>
#include "pair.hpp"

using namespace std;

int main()
{
    Pair<string, int> student("Tom", 19); //实例化出一个类 Pair<string,int>
    Pair<string, int> teacher("David", 20);
    cout << student.key << " " << endl;

    if (student < teacher) {
	cout << "yes";
    }
    return 0;
}

