/*************************************************************************
	> File Name: mutex.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年06月15日 星期四 15时14分38秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <errno.h>

void* Thread_Routine(void *arg)
{
	int *m_arg = (int*)arg;

	while(1)
	{
		if(*m_arg == 1)
			printf("11111111111111111111111111111\n");
		else if(*m_arg == 2)
			printf("22222222222222222222222222222\n");
	}
}

int main(void)
{
	pthread_t m_thread_id_1, m_thread_id_2;
	int arg1, arg2;
	int ret;

	arg1 = 1;
	ret = pthread_create(&m_thread_id_1, NULL, Thread_Routine, &arg1);
	if(ret)
	{
		perror("pthread_create");
		return -1;
	}

	arg2 = 2;
	ret = pthread_create(&m_thread_id_2, NULL, Thread_Routine, &arg2);
	if(ret)
	{
		perror("pthread_create");
		return -1;
	}

	pthread_join(m_thread_id_1, NULL);
	pthread_join(m_thread_id_2, NULL);

	return 0;
}

