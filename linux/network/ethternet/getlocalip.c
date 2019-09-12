/*************************************************************************
	> File Name: getlocalip.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2019年01月10日 星期四 10时19分47秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    char hname[128];
    struct hostent *hent;
    int i;

    gethostname(hname, sizeof(hname));

    //hent = gethostent();
    hent = gethostbyname(hname);

    printf("hostname: %s/naddress list: ", hent->h_name);
    for(i = 0; hent->h_addr_list[i]; i++) {
        printf("%s/t", inet_ntoa(*(struct in_addr*)(hent->h_addr_list[i])));
    }
    return 0;
}
