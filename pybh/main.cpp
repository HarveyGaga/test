#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <algorithm>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

vector<string> vectorFile;

int readFileList(const char *basePath) {
	DIR *dir;
	struct dirent *ptr;
	char base[1000];

	if ((dir = opendir(basePath)) == NULL) {
		perror("Open dir error...");
		exit(1);
	}

	while ((ptr = readdir(dir)) != NULL) {
printf("d_type = %d\n", ptr->d_type);
		if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) ///current dir OR parrent dir
			continue;
		else if (ptr->d_type == 8)    ///file
				{
			//printf("d_name:%s/%s\n",basePath,ptr->d_name);
			string filename = basePath;
			filename += "/";
			filename += ptr->d_name;
			vectorFile.push_back(filename);
		} else if (ptr->d_type == 10)    ///link file
			printf("d_name:%s/%s\n", basePath, ptr->d_name);
		else if (ptr->d_type == 4)    ///dir
				{
			memset(base, '\0', sizeof(base));
			strcpy(base, basePath);
			strcat(base, "/");
			strcat(base, ptr->d_name);
			readFileList(base);
		}
	}
	sort(vectorFile.begin(), vectorFile.end());
	closedir(dir);
	return 1;
}

double compare(const Mat &src1, const Mat &src2) {
	//////////////////////
	//src1变换后实部 planes[0]   虚部planes[1]
	cv::Mat padded1 = src1;
	cv::Mat planes[] = { cv::Mat_<float>(padded1), cv::Mat::zeros(
			padded1.size(), CV_32F) };
	cv::Mat complexI;
	cv::merge(planes, 2, complexI);
	cv::dft(complexI, complexI);
	cv::split(complexI, planes);

	//////////////////////
	//src2变换后实部 planes2[0]  虚部planes2[1]
	cv::Mat padded2 = src2;
	cv::Mat planes2[] = { cv::Mat_<float>(padded2), cv::Mat::zeros(
			padded2.size(), CV_32F) };
	cv::Mat complexI2;
	cv::merge(planes2, 2, complexI2);
	cv::dft(complexI2, complexI2);
	cv::split(complexI2, planes2);

	//////////////////////
	//互功率谱存放矩阵 实部  planes3[0]   虚部planes3[1]
	cv::Mat planes3[] = { cv::Mat::zeros(padded2.size(), CV_32F),
			cv::Mat::zeros(padded2.size(), CV_32F) };

	for (int i = 0; i < padded2.rows; i++) {
		for (int j = 0; j < padded2.cols; j++) {
			//获取像素值
			double r1 = planes[0].at<float>(i, j);
			double i1 = planes[1].at<float>(i, j);
			double r2 = planes2[0].at<float>(i, j);
			double i2 = planes2[1].at<float>(i, j);

			//计算互功率谱的值 cross power spectrum
			double r3 = r1 * r2 + i1 * i2;
			double i3 = r1 * i2 - r2 * i1;
			double abs = sqrt((r3 * r3) + (i3 * i3));
			double r_exp = r3 / abs;
			double i_exp = i3 / abs;

			planes3[0].at<float>(i, j) = r_exp;
			planes3[1].at<float>(i, j) = i_exp;
		}
	}

	// 计算互功率谱的傅立叶反变换
	cv::Mat complexI3;
	cv::merge(planes3, 2, complexI3);
	cv::dft(complexI3, complexI3, CV_DXT_INV_SCALE);//cv::idft(complexI3, complexI3); //idft不可用

	// 求得互功率谱的幅值
	cv::split(complexI3, planes3);
	cv::magnitude(planes3[0], planes3[1], planes3[0]);
	complexI3 = planes3[0];

	double maxVal = 0;
	cv::minMaxLoc(complexI3, NULL, &maxVal, NULL, NULL);

	return maxVal;
}


int main(int argc, char *argv[]) {
	readFileList(argv[1]);
for(size_t i = 0; i < vectorFile.size(); i++) {
	printf("%s\n", vectorFile.at(i).c_str());
}
printf("123\n");
printf("%lu\n", vectorFile.size());
	for(size_t i = 0; i < vectorFile.size()/2; i++) {
		Mat img1 = imread(vectorFile.at(i), IMREAD_GRAYSCALE);
		Mat img2 = imread(vectorFile.at(i+10), IMREAD_GRAYSCALE);
		double score = compare(img1, img2);
		printf("%s - %s:%f\n", vectorFile.at(i).c_str(), vectorFile.at(i+10).c_str(), score);
	}

	return 0;
}
