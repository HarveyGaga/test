/*************************************************************************
	> File Name: select.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年08月21日 星期一 10时56分15秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include <string>

using namespace std;

class Mat
{
	string str;
	int a;
};

void copy(Mat *a, Mat *b)
{
	memcpy(&a, &b, sizeof(Mat));
}

int main(void)
{
	Mat a;
	Mat b;

	copy(&a, &b);

	return 0;
}
