/*************************************************************************
	> File Name: test.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年08月24日 星期五 17时19分38秒
 ************************************************************************/

#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>


#define POINT_NUM 6//不规则矩形顶点数

int wn_PnPoly(CvPoint P, CvPoint* V, int n);
CvPoint vertex_point[POINT_NUM],testpoint;
IplImage *org;
void on_mouse(int EVENT, int x, int y, int flags, void* userdata)
{
    static int i = 0,ii=1;
    CvScalar color_b = CV_RGB(0, 0, 255);
    CvScalar color_r = CV_RGB(255, 0, 0);
    switch (EVENT)
    {
    case CV_EVENT_LBUTTONDOWN:
        if (ii)
        {

            vertex_point[i] = cvPoint(x, y);
            cvCircle(org, vertex_point[i], 1, color_r,2,4,0);
            printf("vertex_point[%d]->(%d,%d)\n", i, vertex_point[i].x, vertex_point[i].y);
            if (i >= 1)
            {
                cvLine(org, vertex_point[i - 1], vertex_point[i], color_r, 3, 4, 0);
                if (i == POINT_NUM - 1)
                {
                    cvLine(org, vertex_point[i], vertex_point[0], color_r, 3, 4, 0);
                    vertex_point[POINT_NUM] = vertex_point[0];
                    ii = 0;
                }
            }
            i++;
        }
        else
        {       
            testpoint=cvPoint(x, y);    
            int out_in=wn_PnPoly(testpoint, vertex_point, POINT_NUM);
            if (out_in==0)//outside
            {
                cvCircle(org, testpoint, 2, color_b, 2, 4, 0);  
                printf("outside!\n");
            }
            else//inside
            {
                cvCircle(org, testpoint, 2, color_r, 2, 4, 0);
                printf("inside!\n");
            }
        //  printf("result:%d", out_in);    
        }
        break;
    default:
        break;
    }

}

inline int isLeft(CvPoint P0, CvPoint P1, CvPoint P2)
{
    return ((P1.x - P0.x) * (P2.y - P0.y)
        - (P2.x - P0.x) * (P1.y - P0.y));
}


int cn_PnPoly(CvPoint P, CvPoint* V, int n)
{
    int    cn = 0;    // the  crossing number counter

                      // loop through all edges of the polygon
    for (int i = 0; i<n; i++) {    // edge from V[i]  to V[i+1]
        if (((V[i].y <= P.y) && (V[i + 1].y > P.y))     // an upward crossing
            || ((V[i].y > P.y) && (V[i + 1].y <= P.y))) { // a downward crossing
                                                          // compute  the actual edge-ray intersect x-coordinate
            float vt = (float)(P.y - V[i].y) / (V[i + 1].y - V[i].y);
            if (P.x <  V[i].x + vt * (V[i + 1].x - V[i].x)) // P.x < intersect
                ++cn;   // a valid crossing of y=P.y right of P.x
        }
    }
    return (cn & 1);    // 0 if even (out), and 1 if  odd (in)

}

int wn_PnPoly(CvPoint P, CvPoint* V, int n)
{
    int    wn = 0;    // the  winding number counter

                      // loop through all edges of the polygon
    for (int i = 0; i<n; i++) {   // edge from V[i] to  V[i+1]
        if (V[i].y <= P.y) {          // start y <= P.y
            if (V[i + 1].y  > P.y)      // an upward crossing
                if (isLeft(V[i], V[i + 1], P) > 0)  // P left of  edge
                    ++wn;            // have  a valid up intersect
        }
        else {                        // start y > P.y (no test needed)
            if (V[i + 1].y <= P.y)     // a downward crossing
                if (isLeft(V[i], V[i + 1], P) < 0)  // P right of  edge
                    --wn;            // have  a valid down intersect
        }
    }
    return wn;
}

int main()
{
    org = cvLoadImage("lena.jpg", CV_LOAD_IMAGE_COLOR);
    cvNamedWindow("lena", CV_WINDOW_AUTOSIZE);
    cvSetMouseCallback("lena", on_mouse, 0);
    while (true)
    {
        cvShowImage("lena", org);
        if (cvWaitKey(20) ==13)break;
    }
    cvReleaseImage(&org);
    cvDestroyAllWindows();
}
