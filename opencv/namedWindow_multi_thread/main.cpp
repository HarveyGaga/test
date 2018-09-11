/*************************************************************************
	> File Name: main.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年01月04日 星期四 14时49分33秒
 ************************************************************************/

#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <X11/Xlib.h>

void* thread_handler(void *arg) {
	const char *name = (const char*)arg;
	cv::Mat image = cv::imread("1.jpg");
	cv::imshow(name, image);
	while(1) {
		printf("%s\n", name);
		cv::waitKey(10);
	}
}

int main(void) {
	gtk_disable_setlocale();
	XInitThreads();

	pthread_t thread_id[2];

	pthread_create(&thread_id[0], NULL, thread_handler, (void*)"1");
	//cv::namedWindow("1", cv::WINDOW_NORMAL);
	pthread_create(&thread_id[0], NULL, thread_handler, (void*)"2");
	//cv::namedWindow("2", cv::WINDOW_NORMAL);


	//pthread_join(thread_id[1], NULL);
	//pthread_join(thread_id[0], NULL);
	while(1) {
		cv::waitKey(10);
	}

	return 0;
}
