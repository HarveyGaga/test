/*************************************************************************
    File Name: video.cpp
    Author: Harvey
    Mail: hanwei@zhihuihutong.com 
    Created Time: 2017年06月16日 星期五 16时21分51秒
 ************************************************************************/

#include <iostream>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>
#include <pthread.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

using namespace cv;  
using namespace std;

#define Log_MainThread(fd,fmt,args...)     do{\
                                            time_t now;\
                                            struct tm *timenow;\
                                            time(&now);\
                                            timenow = localtime(&now);\
                                            fprintf(fd, "[%d-%02d-%02d %02d:%02d:%02d]", 1900+timenow->tm_year, 1+timenow->tm_mon, timenow->tm_mday, timenow->tm_hour, timenow->tm_min, timenow->tm_sec);\
                                            fprintf(fd, fmt, ##args);\
                                        }while(0)


const char *g_cameraIp[] = {
//    "10.100.45.202",
//    "10.100.45.203",
//    "10.100.45.204",
//    "10.100.45.205",
//    "10.100.45.206",
    "10.100.45.203"
};


#if 0
int main_thread(int argc, char **argv){

 

 IplImage *pFrame = NULL, *srcImage=NULL;

 CvCapture *pCapture = NULL;

 //pCapture = cvCaptureFromFile("n:12345@192.168.7.45:554/h264/ch1/main/av_stream");
 pCapture = cvCreateFileCapture("rtsp://10.100.45.205:554/mpeg4?username=admin&password=E10ADC3949BA59ABBE56E057F20F883E");
 //pCapture = cvCreateCameraCapture(1);
 if(!pCapture){
  printf("Can not get the video stream from the camera!\n");
  return -1;
 }

 //read the video by frame
 //while(1)
 while(1){
  //pFrame = cvQueryFrame(pCapture);
  if (srcImage==NULL)
  {
   pFrame = cvQueryFrame(pCapture);
   srcImage=cvCloneImage(pFrame);
   cvShowImage("123234",srcImage);
   //cout<<pFrame->width<<","<<pFrame->height<<endl;
   cvWaitKey(10);
   cvReleaseImage(&srcImage);
   srcImage=NULL;
  }

 }
 cvReleaseCapture(&pCapture);
 cvReleaseImage(&pFrame);


 return 0;
}

#else
void* main_thread(void *arg) {  
    VideoCapture vcap;  
    VideoWriter vwriter;  
    Mat image;
    string m_ip = string((char*)arg);
    struct timespec time_start, time_end;
    long time_count;
    int counter = 0;  
    string videoStreamAddress;
    time_t t_s, t_e;

    FILE *fd;

    fd = fopen(m_ip.c_str(), "w");
    if(fd == NULL)
    {
        Log_MainThread(stdout, "[%s]:%s\n", m_ip.c_str(), strerror(errno));  
        return NULL;
    }
    
    videoStreamAddress += "rtsp://";
    videoStreamAddress += m_ip;
    videoStreamAddress += ":554/mpeg4?username=admin&password=E10ADC3949BA59ABBE56E057F20F883E"; //rtsp://192.168.1.100:554/onvif/live/1  
    Log_MainThread(stdout, "[%s]:", m_ip.c_str());  
    cout << videoStreamAddress << endl;

    if(!vcap.open(videoStreamAddress, CAP_FFMPEG)) {  
        Log_MainThread(stdout, "[%s]:%s", m_ip.c_str(), "Can not get the video stream from the camera!\n");  
        return NULL;
    }  

    t_s = time(NULL);
    //namedWindow(m_ip, WINDOW_GUI_NORMAL);
    for(;;)   
    {  
        //clock_gettime(CLOCK_REALTIME, &time_start);
        counter++;  

        if(!vcap.read(image))   
        {  
            std::cout << "No frame" << std::endl;  
            vcap.release();
            if(!vcap.isOpened())
            {
                Log_MainThread(stdout, "[%s]:camera stream closed!\n", m_ip.c_str());  
                if(!vcap.open(videoStreamAddress, CAP_FFMPEG)) {  
                    Log_MainThread(stdout, "[%s]:%s", m_ip.c_str(), "Can not get the video stream from the camera!\n");  
                    sleep(1);
                    continue;
                }  
            }
        }  
        //printf("cols = %d, rows = %d\n", image.cols, image.rows);
        //clock_gettime(CLOCK_REALTIME, &time_end);
        //time_count = (time_end.tv_nsec - time_start.tv_nsec)/(1000 * 1000);
        //time_count = time_count < 0? time_count + 1000 : time_count;

        t_e = time(NULL);
        if(t_e > t_s)
        {
            Log_MainThread(fd, "帧率%f,%d\n", vcap.get(CAP_PROP_FPS), counter);
            counter = 0;
            t_s = time(NULL);
        }
        fflush(fd);
        
        // if the picture is too large, imshow will display warped images, so show only every 2th frame  
        if (counter %2!= 0)  
            continue;  

        if(image.empty())
        {
            continue;
        }
        
        //imwrite("123.jpg", image);
        //imshow(m_ip, image);  
        //if(waitKey(1) >= 0) break;
        waitKey(1);
        //usleep(1);
    }  

    pthread_exit(0);  
}  
#endif


int main(int argc, char *argv[])
{
    int m_cameraNumber;
    pthread_t m_threadId[10] = {0};
    int i;
    int ret;

    m_cameraNumber = sizeof(g_cameraIp)/sizeof(char*);
    for(i = 0; i < m_cameraNumber; i++)
    {
        ret = pthread_create(&m_threadId[i], NULL, main_thread, (void*)g_cameraIp[i]);
        if(ret != 0)
        {
            perror("pthread_create");
            return -1;
        }
    }

    for(i = 0; i < m_cameraNumber; i++)
    {
        pthread_join(m_threadId[i], NULL);
    }
    
    return 0;
}
