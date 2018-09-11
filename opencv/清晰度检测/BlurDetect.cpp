/*************************************************************************
	> File Name: BlurDetect.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年08月31日 星期五 10时06分13秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <mcheck.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <string>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include "utimer.hpp"
using namespace std;
using namespace cv;

class File {
public:
    std::string path;
    std::string name;

    bool operator<(const File &f1) {
        return this->name < f1.name;
    }
};

void loadImages(const char *p_dirPath, std::vector<File> &image_path_set) {
    char w_filePath[256];

    DIR* w_dir;
    struct dirent* w_entry;

    w_dir = opendir((char*) p_dirPath);
    if (!w_dir) {
        printf("\nError: can't access the folder %s\n", (char* ) p_dirPath);
    }

    printf("图片载入中...\n");

    while ((w_entry = readdir(w_dir)) != NULL) {
        char *w_ext = strrchr(w_entry->d_name, '.');
        if (!w_ext)
            continue;
        if (strcmp(w_ext, ".jpg") && strcmp(w_ext, ".png") && strcmp(w_ext, ".bmp") && strcmp(w_ext, ".jpeg"))
            continue;

        strcpy(w_filePath, (char*) p_dirPath);
        strcat(w_filePath, w_entry->d_name);

        struct stat w_st;
        lstat(w_filePath, &w_st);

        if (!S_ISREG(w_st.st_mode))
            continue;

        File temp;
        temp.path = (char*) p_dirPath;
        temp.name = w_entry->d_name;
        image_path_set.push_back(temp);
    }

    closedir(w_dir);

    printf("载入了%lu个图片\n", image_path_set.size());
    std::sort(image_path_set.begin(), image_path_set.end());
}

/*检测模糊度 
 返回值为模糊度，值越大越模糊，越小越清晰，范围在0到几十，10以下相对较清晰，一般为5。
 调用时可在外部设定一个阀值，具体阈值根据实际情况决定，返回值超过阀值当作是模糊图片。 
 算法所耗时间在1毫秒内
*/
int BlurDetect(const cv::Mat &srcimg)
{
	cv::Mat img;
	cv::cvtColor(srcimg, img, CV_BGR2GRAY); // 将输入的图片转为灰度图，使用灰度图检测模糊度
 
	//图片每行字节数及高  
	int width = img.cols;
	int height = img.rows;
	ushort* sobelTable = new ushort[width*height];
	memset(sobelTable, 0, width*height*sizeof(ushort));
 
	int i, j, mul;
	//指向图像首地址  
	uchar* udata = img.data;
	for (i = 1, mul = i*width; i < height - 1; i++, mul += width)
	for (j = 1; j < width - 1; j++)
 
		sobelTable[mul + j] = abs(udata[mul + j - width - 1] + 2 * udata[mul + j - 1] + udata[mul + j - 1 + width] - \
		udata[mul + j + 1 - width] - 2 * udata[mul + j + 1] - udata[mul + j + width + 1]);
 
	for (i = 1, mul = i*width; i < height - 1; i++, mul += width)
	for (j = 1; j < width - 1; j++)
	if (sobelTable[mul + j] < 50 || sobelTable[mul + j] <= sobelTable[mul + j - 1] || \
		sobelTable[mul + j] <= sobelTable[mul + j + 1]) sobelTable[mul + j] = 0;
 
	int totLen = 0;
	int totCount = 1;
 
	uchar suddenThre = 50;
	uchar sameThre = 3;
	//遍历图片  
	for (i = 1, mul = i*width; i < height - 1; i++, mul += width)
	{
		for (j = 1; j < width - 1; j++)
		{
			if (sobelTable[mul + j])
			{
				int   count = 0;
				uchar tmpThre = 5;
				uchar max = udata[mul + j] > udata[mul + j - 1] ? 0 : 1;
 
				for (int t = j; t > 0; t--)
				{
					count++;
					if (abs(udata[mul + t] - udata[mul + t - 1]) > suddenThre)
						break;
 
					if (max && udata[mul + t] > udata[mul + t - 1])
						break;
 
					if (!max && udata[mul + t] < udata[mul + t - 1])
						break;
 
					int tmp = 0;
					for (int s = t; s > 0; s--)
					{
						if (abs(udata[mul + t] - udata[mul + s]) < sameThre)
						{
							tmp++;
							if (tmp > tmpThre) break;
						}
						else break;
					}
 
					if (tmp > tmpThre) break;
				}
 
				max = udata[mul + j] > udata[mul + j + 1] ? 0 : 1;
 
				for (int t = j; t < width; t++)
				{
					count++;
					if (abs(udata[mul + t] - udata[mul + t + 1]) > suddenThre)
						break;
 
					if (max && udata[mul + t] > udata[mul + t + 1])
						break;
 
					if (!max && udata[mul + t] < udata[mul + t + 1])
						break;
 
					int tmp = 0;
					for (int s = t; s < width; s++)
					{
						if (abs(udata[mul + t] - udata[mul + s]) < sameThre)
						{
							tmp++;
							if (tmp > tmpThre) break;
						}
						else break;
					}
 
					if (tmp > tmpThre) break;
				}
				count--;
 
				totCount++;
				totLen += count;
			}
		}
	}
	//模糊度
	float result = (float)totLen / totCount;
	delete[] sobelTable;
	sobelTable = NULL;
 
	return result;
}

//模糊检测，如果原图像是模糊图像，返回0，否则返回1
double blurDetect(Mat srcImage)
{
 
	Mat gray1;
	if (srcImage.channels() != 1)
	{
		//进行灰度化
		cvtColor(srcImage, gray1, CV_RGB2GRAY);
	}
	else
	{
		gray1 = srcImage.clone();
	}
	Mat tmp_m1, tmp_sd1;	//用来存储均值和方差
	double m1 = 0, sd1 = 0;
	//使用3x3的Laplacian算子卷积滤波
	Laplacian(gray1, gray1, CV_16S, 3);
	//归到0~255
	convertScaleAbs(gray1, gray1);
	//计算均值和方差
	meanStdDev(gray1, tmp_m1, tmp_sd1);
	m1 = tmp_m1.at<double>(0, 0);		//均值
	sd1 = tmp_sd1.at<double>(0, 0);		//标准差
	//cout << "原图像：" << endl;
	//cout << "均值: " << m1 << " , 方差: " << sd1*sd1 << endl;
	return sd1*sd1;
}

int main(int argc, char **argv) {
	std::vector<File> image_set;
	loadImages(argv[1], image_set);

	for (size_t i = 0; i < image_set.size();i++) {
		string file = image_set[i].path + image_set[i].name;
		cv::Mat image = cv::imread(file);

		if (!image.empty()) {
			UTimer timer;
			timer.Start();
			//int val = VideoBlurDetect(image);
			double val = blurDetect(image);
			printf("cost %fms\t\t", timer.Elapse()*1000);
			printf("%s = %f\n", image_set[i].name.c_str(), val);
#if 1
			cv::namedWindow(image_set[i].name, CV_WINDOW_NORMAL);
			cv::imshow(image_set[i].name, image);
			cv::resizeWindow(image_set[i].name, image.cols/2, image.rows/2);
			int key = cv::waitKey();
			cv::destroyWindow(image_set[i].name);
			switch(key) {
			case 'q':
				return 0;
			case 65362:
				i > 0 ? i -= 2 : i = 0;
				break;
			default:
				i++;
			}
#endif

		}
	}


	return 0;
}

