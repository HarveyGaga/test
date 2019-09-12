/*************************************************************************
	> File Name: test.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年12月25日 星期二 13时53分04秒
 ************************************************************************/

#include<string>
#include<stdio.h>
#include<unistd.h>
#include<opencv2/opencv.hpp>


int main(int argc, char **argv) {
	int ret;
	ret = access(argv[1], W_OK | X_OK);
	if (ret != 0) {
		printf("dir not W_OK|X_OK.\n");
	} else {
		printf("dir W_OK|X_OK.\n");
	}

	cv::Mat img = cv::imread("1.jpg");
	if (img.empty()) {
		printf("read image failed.\n");
		return -1;
	}

	try {
		bool r = cv::imwrite(std::string(argv[1]) + "/1.jpg", img);
		printf("save img %s.\n", r? "ok":"failed");
	} catch (cv::Exception &e) {
		printf("%s\n", e.what());
	}

	return 0;
}
