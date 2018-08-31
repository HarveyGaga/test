

#include <iostream>
#include <stdio.h>
#include <list>
#include "opencv2/core/core.hpp" 
#include "opencv2/highgui/highgui.hpp" 
#include "opencv2/imgproc/imgproc.hpp" 
#include <sys/time.h>
#include <sys/resource.h>


//#include <libavcodec/avcodec.h>
//#include <libavformat/avformat.h>
//#include <libswscale/swscale.h>
//#include <libavutil/imgutils.h>
////#include "libavcodec/internal.h"

//#include "Engine.h" 

#include <unistd.h>
#include <queue>
#include "video_api.h"

using namespace std;
using namespace cv;

static char filepath[6][256] = 
{
{"rtsp://10.100.45.202:554/mpeg4?username=admin&password=E10ADC3949BA59ABBE56E057F20F883E"},
{"rtsp://10.100.45.203:554/mpeg4?username=admin&password=E10ADC3949BA59ABBE56E057F20F883E"},
{"rtsp://10.100.45.204:554/mpeg4?username=admin&password=E10ADC3949BA59ABBE56E057F20F883E"},
{"rtsp://10.100.45.205:554/mpeg4?username=admin&password=E10ADC3949BA59ABBE56E057F20F883E"},
{"rtsp://10.100.45.206:554/mpeg4?username=admin&password=E10ADC3949BA59ABBE56E057F20F883E"},
{"rtsp://10.100.45.207:554/mpeg4?username=admin&password=E10ADC3949BA59ABBE56E057F20F883E"},
};

/*测试ffmpeg效果*/
int main(int argc,char* argv[])
{
    pthread_t thread_id[8];
    int i ;

    ffmpeg_all_init();

    for(i = 0;i < 1;i++)
    {
        create_ffmpeg_thread(&thread_id[i],filepath[1]);
    }    
#if 0
    for(i = 0;i < 4;i++)
    {
        create_ffmpeg_thread(&thread_id[i+4],filepath[i]);
    } 
#endif
#if 1
    for(i = 0;i < 1;i++)
    {
        pthread_join(thread_id[i],NULL);
    }
#endif
    
    return 0;
}

