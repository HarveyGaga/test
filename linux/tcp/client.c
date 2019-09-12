/*************************************************************************
	> File Name: client.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年10月19日 星期五 18时53分30秒
 ************************************************************************/

#include<stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(){
    int socketFd = -1;  
    struct sockaddr_in server_add;
    char inputBuf[11];
    int output;
    unsigned short portnum = htons(12001);
    server_add.sin_family = AF_INET;
    server_add.sin_port = portnum;
    inet_aton("39.107.79.218", &server_add.sin_addr);

    printf("Create Socket\n");
    if( (socketFd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        printf("Fail on Creating Socket\n");
        exit(1);
    }

    printf("Connet the Server\n");
    if( connect(socketFd, (struct sockaddr*) &server_add, sizeof(struct sockaddr_in)) != 0 ){
        printf("Fail on Connecting\n");
        exit(1);
    }   

    while(1){
        memset(inputBuf, 0, sizeof(inputBuf));
        printf("Connected, Please Enter Number:\n");
        scanf("%s",inputBuf);
        if(strncmp(inputBuf, "end", 3) == 0) break;
        write(socketFd, inputBuf, strlen(inputBuf));
        memset(inputBuf, 0, sizeof(inputBuf));
        while(!read(socketFd, inputBuf, 11));
        output = atoi(inputBuf);
        printf("Result is %d\n", output);
    }

    close(socketFd);
    return 0;
}
