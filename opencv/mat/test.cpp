/*************************************************************************
	> File Name: test.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年07月20日 星期四 15时04分47秒
 ************************************************************************/

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main(void)
{
	Mat image = imread("./123.jpg");
	Mat image2;
	int buffer[100];

	printf("%x, %x\n", buffer, &buffer);

	image.copyTo(image2);
	printf("%x\n", &image);
	printf("%x\n", &image2);
	printf("%x\n", image.data);
	printf("%x\n", image2.data);
	printf("%d, %d\n", image2.rows, image2.cols);


	putText(image,"1234567890",Point(0,image.rows/2),CV_FONT_HERSHEY_SIMPLEX,2,Scalar(0,0,255),10);
	imshow("123", image);
	imshow("image2", image2);
	waitKey();


	return 0;
}
