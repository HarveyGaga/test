/*************************************************************************
> File Name: carCheck.cpp
> Author: Harvey
> Mail: hanwei@zhihuihutong.com 
> Created Time: 2017年07月06日 星期四 16时09分30秒
 ************************************************************************/

#include <opencv2/opencv.hpp>  
#include <opencv2/core/types_c.h>  
#include <opencv2/core/utility.hpp>  
#include <opencv2/tracking.hpp>  
#include <opencv2/videoio.hpp>  
#include <opencv2/highgui.hpp>  
#include <opencv2/video/background_segm.hpp>  
#include <iostream>  
#include <cstring>  

using namespace std;  
using namespace cv;  


void processVideo(char* videoFilename)  
{  
    Mat frame; // current frame  
    Mat fgMaskMOG2; // fg mask fg mask generated by MOG2 method  
    Mat bgImg; // background  
    Ptr<BackgroundSubtractorMOG2> pMOG2 = createBackgroundSubtractorMOG2(200, 36.0, false); // MOG2 Background subtractor  
  
    while (true)  
    {  
        VideoCapture capture(videoFilename);  
        if (!capture.isOpened())  
        {  
            cerr << "Unable to open video file: " << videoFilename << endl;  
            return;  
        }  
  
        int width = (int)capture.get(CV_CAP_PROP_FRAME_WIDTH);  
        int height = (int)capture.get(CV_CAP_PROP_FRAME_HEIGHT);  
  
        //unique_ptr<IplImage, void(*)(IplImage*)> labelImg(cvCreateImage(cvSize(width, height), IPL_DEPTH_LABEL, 1),   
        //    [](IplImage* p){ cvReleaseImage(&p); });  
        IplImage *labelImg = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 1);
        CvBlobs blobs;  
        CvTracks tracks;  
  
        while (true)  
        {  
            // read input data. ESC or 'q' for quitting  
            int key = waitKey(1);  
            if (key == 'q' || key == 27)  
                return;  
            if (!capture.read(frame))  
                break;  
  
            // update background  
            pMOG2->apply(frame, fgMaskMOG2);  
            pMOG2->getBackgroundImage(bgImg);  
            imshow("BG", bgImg);  
            imshow("Original mask", fgMaskMOG2);  
  
            // post process  
            medianBlur(fgMaskMOG2, fgMaskMOG2, 5);  
            imshow("medianBlur", fgMaskMOG2);  
            morphologyEx(fgMaskMOG2, fgMaskMOG2, MORPH_CLOSE, getStructuringElement(MORPH_RECT, Size(5, 5))); // fill black holes  
            morphologyEx(fgMaskMOG2, fgMaskMOG2, MORPH_OPEN, getStructuringElement(MORPH_RECT, Size(5, 5))); // fill white holes  
            imshow("morphologyEx", fgMaskMOG2);  
  
            // track  
            cvLabel(&IplImage(fgMaskMOG2), labelImg.get(), blobs);  
            cvFilterByArea(blobs, 64, 10000);  
            cvUpdateTracks(blobs, tracks, 10, 90, 30);  
            cvRenderTracks(tracks, &IplImage(frame), &IplImage(frame));  
  
            // show  
            imshow("Frame", frame);  
  
            key = waitKey(30);  
        }  
    }  
} 

int main(void)
{
    processVideo("132941-vv-1.avi");

    return 0;
}
