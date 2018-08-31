/*************************************************************************
	> File Name: main.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年12月13日 星期三 09时53分04秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

#include <unistd.h>


void sig_handler(int s)
{
    psignal(s, "Hello,kity\n");
}

void timer_thread(union sigval v)
{
    printf("hello,world! %d\n", v.sival_int);
}

int main()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    if(sigaction(SIGUSR1, &sa, 0) < 0) {
        perror("sigaction");
        exit(1);
    }
    if(sigaction(SIGUSR2, &sa, 0) < 0) {
        perror("sigaction");
        exit(1);
    }

    timer_t t1, t2;
    struct sigevent se;
    memset(&se, 0, sizeof(struct sigevent));

    se.sigev_value.sival_int = 999;
    se.sigev_signo = SIGUSR1;
    se.sigev_notify = SIGEV_SIGNAL;
    se.sigev_notify = SIGEV_THREAD;
    se.sigev_notify_function = timer_thread;

    if(timer_create(CLOCK_REALTIME, &se, &t1) < 0) {
        perror("timer_create");
        exit(1);
    }

    se.sigev_value.sival_int = 777;
    //se.sigev_signo = SIGUSR2;
    if(timer_create(CLOCK_REALTIME, &se, &t2) < 0) {
        perror("timer_create");
        exit(1);
    }

    struct itimerspec it;
    it.it_interval.tv_sec = 3;
    it.it_interval.tv_nsec = 0;
    it.it_value.tv_sec = 0;
    it.it_value.tv_nsec = 20000;
    if(timer_settime(t1, 0, &it, 0) < 0) {
        perror("timer_settime");
        exit(1);
    }

    it.it_interval.tv_sec = 5;
    it.it_interval.tv_nsec = 0;
    it.it_value.tv_sec = 0;
    it.it_value.tv_nsec = 50000;
    if(timer_settime(t2, 0, &it, 0) < 0) {
        perror("timer_settime");
        exit(1);
    }

    pause();

    return 0;
}

