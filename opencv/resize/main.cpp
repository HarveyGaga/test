/*************************************************************************
	> File Name: main.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年12月12日 星期二 10时41分02秒
 ************************************************************************/

#include<iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;


int main (void) {
	Mat image = imread("image.jpg");

	Mat dest;
	resize(image, dest, Size(400, 300), (0, 0), (0, 0), cv::INTER_LINEAR);
#if 0
	imshow("image", image);
	imshow("dest", dest);
	waitKey();
#endif
	while(1);

	return 0;
}
