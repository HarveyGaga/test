/*************************************************************************
	> File Name: main.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年01月09日 星期二 11时20分31秒
 ************************************************************************/

#include<iostream>

class string {
	public:
		explicit string (const int i) {
			data = i;
		}

		void print(void) {
			std::cout << data << std::endl;
		}

	private:
		int data;
};

int main() {
	string str(1);
	str.print();
}
