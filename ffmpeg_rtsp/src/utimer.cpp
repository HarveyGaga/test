/**   
 * @Title: utimer.cpp 
 * @Description: TODO(用一句话描述该文件做什么) 
 * @author Harvey
 * @date 2017年9月30日 下午3:18:18 
 * @version V1.0   
 */
#include "utimer.hpp"
#include <time.h>

UTimer::UTimer() {
	// TODO Auto-generated constructor stub
	is_pause = false; //初始化计时器状态
	is_stop = true;
}

UTimer::~UTimer() {
	// TODO Auto-generated destructor stub
}

bool UTimer::isPause() {
	if (is_pause)
		return true;
	else
		return false;
}
bool UTimer::isStop() {
	if (is_stop)
		return true;
	return false;
}
void UTimer::Start() {
	if (is_stop) {
		gettimeofday(&start_time, NULL);
		is_stop = false;
	} else if (is_pause) {
		is_pause = false;
		struct timeval temp;
		gettimeofday(&temp, NULL);
		//更新开始时间：用此时的时间 - 暂停时所用的时间 + 上一次开始的时间 = 此时的开始时间
		start_time.tv_sec += temp.tv_sec - pause_time.tv_sec;
		start_time.tv_usec += temp.tv_usec - pause_time.tv_usec;
	}
}
void UTimer::Pause() {
	if (is_stop || is_pause) //如果处于停止/暂停状态,此动作不做任何处理，直接返回
		return;
	else    //否则调制为暂停状态
	{
		is_pause = true;
		gettimeofday(&pause_time, NULL); //获取暂停时间
	}
}
double UTimer::Elapse() {
	double timeLapse;
	struct timeval endtime;

	gettimeofday(&endtime, NULL);
	timeLapse = 1000000 * (endtime.tv_sec - start_time.tv_sec) + endtime.tv_usec - start_time.tv_usec;
	timeLapse /= 1000000;/*转换成秒输出*/

	return timeLapse;
}

// 返回自系统开机以来的毫秒数（tick）
unsigned long UTimer::GetTickCount(void) {
	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
