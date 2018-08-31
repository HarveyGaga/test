/**   
 * @Title: utimer.hpp 
 * @Description: TODO(用一句话描述该文件做什么) 
 * @author Harvey
 * @date 2017年9月30日 下午3:18:17 
 * @version V1.0   
 */
#ifndef SRC_UTILITY_UTIMER_HPP_
#define SRC_UTILITY_UTIMER_HPP_

/** 
 * @ClassName: UTimer 
 * @Description: TODO(这里用一句话描述这个类的作用) 
 * @author vmuser
 * @date 2017年9月30日 下午3:18:17 
 * 
 * 
 */

#include<sys/time.h>

class UTimer {
public:
	UTimer();
	~UTimer();

	bool isPause(); //返回计时器状态
	bool isStop();
	//计时器的三种动作（功能）
	void Start();
	void Pause();
	double Elapse();

	// 返回自系统开机以来的毫秒数（tick）
	static unsigned long GetTickCount(void);

private:
	struct timeval start_time;
	struct timeval pause_time;
	//两个bool值标记四种状态
	bool is_pause; //记录计时器的状态 （是否处于暂停状态）
	bool is_stop; //是否处于停止状态

};

#endif /* SRC_UTILITY_UTIMER_HPP_ */
