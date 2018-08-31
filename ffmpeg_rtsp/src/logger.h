#ifndef _LOGGER_H_
#define _LOGGER_H_
#include <syslog.h>
#include <string.h>
#ifdef __cplusplus
extern "C"
{
#endif

#define filename(x) strrchr(x,'/')?strrchr(x,'/')+1:x

/*调试模式*/
#define DEBUG

#ifdef DEBUG

#define DBG(fmt, args...) printf("[%s-%d](DBG):"fmt"\n",filename(__FILE__), __LINE__,   ##args)
#define INFO(fmt, args...) printf("[%s-%d](INFO):"fmt"\n",filename(__FILE__), __LINE__,  ##args)
#define WARNING(fmt, args...) printf("[%s-%d](WARNING):"fmt"\n",filename(__FILE__), __LINE__,   ##args)
#define ERR(fmt, args...) printf("[%s-%d](ERR):%m"fmt"\n",filename(__FILE__), __LINE__,  ##args)

#else 
#define DBG_F(facility,fmt,args...) syslog(LOG_DEBUG|facility,"[%s-%d](DBG):"fmt"\n", filename(__FILE__), __LINE__, ##args)
#define DBG(fmt, args...) syslog(LOG_DEBUG|LOG_LOCAL7,"[%s-%d](DBG):"fmt"\n", filename(__FILE__), __LINE__, ##args)
#define INFO(fmt, args...) syslog(LOG_INFO|LOG_LOCAL7,"[%s-%d](INFO):"fmt"\n", filename(__FILE__), __LINE__, ##args)
#define WARNING(fmt, args...) syslog(LOG_WARNING|LOG_LOCAL7,"[%s-%d](WARNING):"fmt"\n", filename(__FILE__), __LINE__, ##args)
#define ERR(fmt, args...) syslog(LOG_ERR|LOG_LOCAL7,"[%s-%d](ERR):"fmt"-%m\n", filename(__FILE__), __LINE__, ##args)
#endif
#ifdef __cplusplus
}
#endif

#endif
