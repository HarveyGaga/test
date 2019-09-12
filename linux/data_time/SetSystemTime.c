/*************************************************************************
	> File Name: SetSystemTime.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2019年01月10日 星期四 17时38分40秒
 ************************************************************************/
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <errno.h>
#include <string.h>

/************************************************ 
设置操作系统时间 
参数:*dt数据格式为"2006-4-20 20:30:30" 
调用方法: 
    char *pt="2006-4-20 20:30:30"; 
    SetSystemTime(pt); 
**************************************************/  
int SetSystemTime(char *dt) {
    struct tm _tm;
    struct timeval tv;
    time_t timep;
    
    _tm.tm_year = 2019 - 1900;
    _tm.tm_mon = 1 - 1;
    _tm.tm_mday = 10;
    _tm.tm_hour = 17;
    _tm.tm_min = 12;
    _tm.tm_sec = 12;

    timep = mktime(&_tm);
    tv.tv_sec = timep;
    tv.tv_usec = 0;
    if (settimeofday(&tv, NULL) < 0) {
        printf("Set system datatime error:%s\n", strerror(errno));
        return -1;
    }
    printf("Set system datatime ok!\n");
    return 0;
}



int main(int argc, char **argv) {
	SetSystemTime(argv[1]);

	return 0;
}
