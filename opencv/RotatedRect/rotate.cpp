/*************************************************************************
	> File Name: rotate.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年08月30日 星期四 10时08分49秒
 ************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;



int main(int argc, char **argv){
    cv::Mat src = cv::imread(argv[1]);
    cv::imshow("src", src);
    double angle = atoi(argv[2]);
    angle = -angle;
    cv::Point2f center(src.cols / 2, src.rows / 2);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1);
    cv::imshow("rot", rot);
    cv::Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();

    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

    cv::Mat dst;
    cv::warpAffine(src, dst, rot, bbox.size());
    cv::imshow("dst", dst);
    cv::waitKey(0);

}
