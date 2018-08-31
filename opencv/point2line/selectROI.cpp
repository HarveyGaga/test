/*
 * selectROI.cpp
 *
 *  Created on: 2017年11月22日
 *      Author: vmuser
 */

#include "selectROI.hpp"
#include <stdio.h>

/*
static int calc_cross(cv::Point pa, cv::Point pb , cv::Point pc)
*@ brief:叉积计算一个点在另两个点所在的直线的上面还是下面
*@param
*@return 无
*/
int calc_cross(cv::Point pa, cv::Point pb , cv::Point pc)
{
	int ret = (pb.x-pa.x)*(pc.y-pa.y) - (pb.y-pa.y)*(pc.x-pa.x);
	return ret>0? 1 : 0;
}

const std::string windowName = "selectROI";

cv::Mat org, img, tmp;
cv::Rect roi;
void on_mouse(int event, int x, int y, int flags, void *ustc) //event鼠标事件代号，x,y鼠标坐标，flags拖拽和键盘操作的代号
		{
	static cv::Point pre_pt(-1, -1); //初始坐标
	static cv::Point pre1_pt(-1, -1);
	static cv::Point cur_pt(-1, -1); //实时坐标
	static bool ok = false;
	char temp[16];
	if (event == CV_EVENT_LBUTTONDOWN) //左键按下，读取初始坐标，并在图像上该点处划圆
			{
		printf("mouse down(%d,%d)\n", x, y);
		org.copyTo(img); //将原始图片复制到img中
		sprintf(temp, "(%d,%d)", x, y);
		pre_pt = cv::Point(x, y);
		cv::putText(img, temp, pre_pt, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0, 255), 1, 8); //在窗口上显示坐标

		imshow(windowName, img);
	} else if (event == CV_EVENT_MOUSEMOVE && !(flags & CV_EVENT_FLAG_LBUTTON)) //左键没有按下的情况下鼠标移动的处理函数
			{
		printf("mouse up move(%d,%d)\n", x, y);
		img.copyTo(tmp); //将img复制到临时图像tmp上，用于显示实时坐标
		cur_pt = cv::Point(x, y);
		if (!ok) {
			sprintf(temp, "(%d,%d)", x, y);
			
		} else {
			int ret = calc_cross(pre_pt, pre1_pt, cur_pt);
			sprintf(temp, "(%d,%d,%d)", x, y, ret);
		}
		cv::putText(tmp, temp, cur_pt, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0, 255)); //只是实时显示鼠标移动的坐标
		imshow(windowName, tmp);
	} else if (event == CV_EVENT_MOUSEMOVE && (flags & CV_EVENT_FLAG_LBUTTON)) //左键按下时，鼠标移动，则在图像上划矩形
			{
		printf("mouse down move(%d,%d)\n", x, y);
		img.copyTo(tmp);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = cv::Point(x, y);
		cv::putText(tmp, temp, cur_pt, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0, 255));
		cv::line(tmp, pre_pt, cur_pt, cv::Scalar(0, 255, 0, 0), 1, 8, 0); //在临时图像上实时显示鼠标拖动时形成的矩形
		imshow(windowName, tmp);
	} else if (event == CV_EVENT_LBUTTONUP) //左键松开，将在图像上划矩形
			{
		printf("mouse up(%d,%d)\n", x, y);
		org.copyTo(img);
		sprintf(temp, "(%d,%d)", x, y);
		cur_pt = cv::Point(x, y);
		pre1_pt = cur_pt;
		ok = true;
		cv::putText(img, temp, cur_pt, cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0, 255));
		cv::line(img, pre_pt, cur_pt, cv::Scalar(0, 255, 0, 0), 1, 8, 0); //根据初始点和结束点，将矩形画到img上
		cv::imshow(windowName, img);
//        img.copyTo(tmp);

		int width = abs(pre_pt.x - cur_pt.x);
		int height = abs(pre_pt.y - cur_pt.y);
		roi = cv::Rect(std::min(cur_pt.x, pre_pt.x), std::min(cur_pt.y, pre_pt.y), width, height);
	}
}

cv::Rect selectROI(cv::Mat &image) {
	image.copyTo(org);
	org.copyTo(img);
	org.copyTo(tmp);
//	cv::namedWindow(windowName, CV_WINDOW_NORMAL);
	cv::namedWindow(windowName);
	cv::setMouseCallback(windowName, on_mouse, 0); //调用回调函数
	cv::imshow(windowName, img);
	cv::waitKey();
	cv::destroyWindow("selectROI");

	return roi;
}

int main(void) {
	cv::Mat image = cv::imread("./1.png");
	if (image.empty())
		return -1;

	selectROI(image);

	return 0;
}
