/*************************************************************************
	> File Name: getlocalip_socket.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2019年01月10日 星期四 10时23分54秒
 ************************************************************************/
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
void GetLocalIp()  
{  
  
    int sock_get_ip;  
    char ipaddr[50];  
  
    struct   sockaddr_in *sin;  
    struct   ifreq ifr_ip;     
  
    if ((sock_get_ip=socket(AF_INET, SOCK_STREAM, 0)) == -1)  
    {  
         printf("socket create failse...GetLocalIp!/n");  
         return;  
    }  
     
    memset(&ifr_ip, 0, sizeof(ifr_ip));     
    strncpy(ifr_ip.ifr_name, "ens33", sizeof(ifr_ip.ifr_name) - 1);     
   
    if( ioctl( sock_get_ip, SIOCGIFADDR, &ifr_ip) < 0 )     
    {     
	perror("ioctl");
         return;     
    }       
    sin = (struct sockaddr_in *)&ifr_ip.ifr_addr;     
    strcpy(ipaddr,inet_ntoa(sin->sin_addr));         
      
    printf("local ip:%s /n",ipaddr);      
    close( sock_get_ip );
}

int main()
{
   GetLocalIp();
   return 0;
}
