/*************************************************************************
	> File Name: openImage.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年06月13日 星期二 19时49分25秒
 ************************************************************************/

#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
 
using namespace cv;
using namespace std;
 
int main(int argc, const char** argv)
{
    Mat img(500, 1000, CV_8UC3, Scalar(0, 0, 100)); //创建一个图像 ( 3个通道, 8 bit位深, 高500, 宽1000, (0, 0, 100) 分别分配给 Blue, Green and Red. )
 
    if (img.empty())
    {
        cout << "图像不能加载！" << endl;
        //system("pause");
        return -1;
    }
 
    return 0;
}
