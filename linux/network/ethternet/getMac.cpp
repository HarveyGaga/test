/*************************************************************************
	> File Name: getMac.cpp
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2019年01月10日 星期四 20时16分04秒
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
#include <string>

std::string GetMac() {
    struct ifreq ifreq;
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
    }
    strcpy(ifreq.ifr_name, "ens33");    //Currently, only get eth0
    if (ioctl(sock, SIOCGIFHWADDR, &ifreq) != -1) {

    }
    close(sock);
    char tBuf[32];
    snprintf(tBuf, sizeof(tBuf), "%02X:%02X:%02X:%02X:%02X:%02X", ifreq.ifr_hwaddr.sa_data[0], ifreq.ifr_hwaddr.sa_data[1], ifreq.ifr_hwaddr.sa_data[2], ifreq.ifr_hwaddr.sa_data[3], ifreq.ifr_hwaddr.sa_data[4], ifreq.ifr_hwaddr.sa_data[5]);

    return tBuf;
}

int main() {
    printf("%s\n", GetMac().c_str());
    return 0;
}
