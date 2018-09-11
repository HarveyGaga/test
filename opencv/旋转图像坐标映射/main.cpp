//============================================================================
// Name        : test.cpp
// Author      : Harvey
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <signal.h>
#include <vector>
#include <algorithm>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

void ImgRotate(const cv::Mat &src, cv::Mat &dst, double angle) {
    if (src.empty())
        return;

    cv::Point2f center(src.cols / 2, src.rows / 2);
    cv::Mat rot = cv::getRotationMatrix2D(center, angle, 1);
    cv::Rect bbox = cv::RotatedRect(center, src.size(), angle).boundingRect();

    rot.at<double>(0, 2) += bbox.width / 2.0 - center.x;
    rot.at<double>(1, 2) += bbox.height / 2.0 - center.y;

    cv::warpAffine(src, dst, rot, bbox.size(), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255));
}

cv::Point2f GetPointAffinedPos(Mat & src, Mat & dst, const cv::Point2f &src_p, const cv::Point2f center, double angle, double scale) {
    angle = angle * CV_PI / 180;
    double alpha = cos(angle) * scale;
    double beta = sin(angle) * scale;

    int width = src.cols;
    int height = src.rows;

    Point2f dst_p;
    int x = src_p.x - center.x;
    int y = src_p.y - center.y;

    dst_p.x = cvRound(x * alpha + y * beta + center.x);
    dst_p.y = cvRound(-x * beta + y * alpha + center.y);

    int new_width = dst.cols;
    int new_height = dst.rows;

    int movx = (int) ((new_width - width) / 2);
    int movy = (int) ((new_height - height) / 2);

    dst_p.x += movx;
    dst_p.y += movy;

    return dst_p;
}

int main() {
    Mat carImage = imread("1536622667_249_524_179_111_org.jpg");
//    Mat carImage = imread("1536589654_358_331_153_97_org.jpg");

    cv::Mat rotateCarImage;
    //旋转角度-20度
    double plateImgRotateAngle = -20;
    ImgRotate(carImage, rotateCarImage, plateImgRotateAngle);

    cv::Rect rotatedPlateRect(433, 649, 168, 54);
//    cv::Rect rotatedPlateRect(427, 481, 143, 48);
    cv::rectangle(rotateCarImage, rotatedPlateRect, cv::Scalar(0,0,255), 2);

    cv::Point2f rotateCarImageCenter(rotateCarImage.cols / 2, rotateCarImage.rows / 2);
    cv::Point2f rotatePlateCenter(rotatedPlateRect.x + rotatedPlateRect.width / 2, rotatedPlateRect.y + rotatedPlateRect.height / 2);
    cv::Point2f orgPlateCenter = GetPointAffinedPos(rotateCarImage, carImage, rotatePlateCenter, rotateCarImageCenter, -plateImgRotateAngle, 1.0);
    /* 车牌在原图使用旋转矩阵表示 */
    cv::RotatedRect orgPlatePos(orgPlateCenter, cv::Size2f(rotatedPlateRect.width, rotatedPlateRect.height), plateImgRotateAngle);
    cv::Rect_<float> orgPlateBoundingRect = orgPlatePos.boundingRect();
    printf("%.0f, %.0f, %.0f, %.0f\n", orgPlateBoundingRect.x, orgPlateBoundingRect.y, orgPlateBoundingRect.width, orgPlateBoundingRect.height);
    cv::rectangle(carImage, orgPlateBoundingRect, cv::Scalar(0,0,255), 2);

    Point2f vertices[4];
    orgPlatePos.points(vertices);
    for (int i = 0; i < 4; i++)
        cv::line(carImage, vertices[i], vertices[(i+1)%4], Scalar(0,255,0));

    cv::imshow("src Image", carImage);
    cv::imshow("Rotation Image", rotateCarImage);

    waitKey(0);
    return 0;
}
