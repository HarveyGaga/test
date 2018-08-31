/*************************************************************************
	> File Name: test.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年05月02日 星期二 15时26分08秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<time.h>


static void StrToTime(time_t *tm, const char *str)
{
    struct tm m_tm;
    const char *m_pstr = str;
    char m_pBuffer[6];

    strncpy(m_pBuffer, m_pstr, 4);
    m_pBuffer[4] = '\0';
    m_tm.tm_year = atoi(m_pBuffer);
    m_tm.tm_year -= 1900;
    m_pstr += 4;
    strncpy(m_pBuffer, m_pstr, 2);
    m_pBuffer[2] = '\0';
    m_tm.tm_mon = atoi(m_pBuffer);
    m_pstr += 2;
    strncpy(m_pBuffer, m_pstr, 2);
    m_pBuffer[2] = '\0';
    m_tm.tm_mday = atoi(m_pBuffer);
    m_pstr += 2;
    strncpy(m_pBuffer, m_pstr, 2);
    m_pBuffer[2] = '\0';
    m_tm.tm_hour = atoi(m_pBuffer);
    m_pstr += 2;
    strncpy(m_pBuffer, m_pstr, 2);
    m_pBuffer[2] = '\0';
    m_tm.tm_min = atoi(m_pBuffer);
    m_pstr += 2;
    strncpy(m_pBuffer, m_pstr, 2);
    m_pBuffer[2] = '\0';
    m_tm.tm_sec = atoi(m_pBuffer);
    m_pstr += 2;
    
	printf("%d-%d-%d %d:%d:%d\n", m_tm.tm_year+1900,
								  m_tm.tm_mon,
								  m_tm.tm_mday,
								  m_tm.tm_hour,
								  m_tm.tm_min,
								  m_tm.tm_sec);
}



int main(void)
{
	time_t m_time;

	StrToTime(&m_time, "20170518184521");

	return 0;
}
