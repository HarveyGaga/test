/*************************************************************************
	> File Name: test.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年08月27日 星期一 18时42分26秒
 ************************************************************************/

#include<iostream>
#include<stdio.h>
#include<opencv2/opencv.hpp>
using namespace std;
/*
static int calc_cross(cv::Point pa, cv::Point pb , cv::Point pc)
*@ brief:叉积计算一个点在另两个点所在的直线的上面还是下面
*@param
*@return 无
*/
int calc_cross(cv::Point pa, cv::Point pb , cv::Point pc)
{
    return (pb.x-pa.x)*(pc.y-pa.y) - (pb.y-pa.y)*(pc.x-pa.x);
}

int main(int argc, char **argv) {
    cv::Point pa(0, 0);
    cv::Point pb(100, 100);
    cv::Point pc(10,80);

    int ret = calc_cross(pa, pb, pc);
    printf("ret = %d\n", ret);

    return 0;
}
