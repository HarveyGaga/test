/*
 * server.cpp
 *
 *  Created on: Nov 15, 2016
 *      Author: zp
 */



#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>


#include "server.h"

/*
 * function : initSocket
 *
 * description : 1. open socket
 *               2. bind ip
 *               3. accpt client
 *
 * output :
 *
 * intput :
 *
 *
 * return : 0---SUCCESS; other ---- FAILED
 * **/
int tcp_server::initSocket(char *ip,int port)
{
    int ret = 0;

    socklen_t sin_size;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		fprintf(stderr, "Socket error:%s\n\a", strerror(errno));
		return -1;
	}
	bzero(&server_addr, sizeof(struct sockaddr_in));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(port);
	if (bind(sockfd, (struct sockaddr *) (&server_addr),
			sizeof(struct sockaddr)) == -1)
	{
		fprintf(stderr, "Bind error:%s\n\a", strerror(errno));
		return -2;
	}
	if (listen(sockfd, 5) == -1)
	{
		fprintf(stderr, "Listen error:%s\n\a", strerror(errno));
		return -3;
	}

	sin_size = sizeof(struct sockaddr_in);

	if ((new_fd = accept(sockfd, (struct sockaddr *) (&client_addr),&sin_size)) == -1)
	{
		fprintf(stderr, "Accept error:%s\n\a", strerror(errno));
		return -4;
	}

    return ret;
}

/*
 * function : sendSockset
 *
 * description : socket send data
 *
 *
 * intput : send data
 *
 * output : NULL
 *
 * return : 0---SUCCESS; other ---- FAILED
 * */
int tcp_server::sendSockset(char *sendData)
{
    int ret = 0;
    ret = send(new_fd, sendData, sizeof(sendData), 0);


    return ret;
}
/*
 * function : recvSocket
 *
 * description : recv data from socket
 *
 * input : send data
 *
 * output: NULL
 *
 * return : 0---SUCCESS; other ---- FAILED
 * */
int tcp_server::recvSocket(char *recvBuf,int size)
{
    int ret = 0;
    ret = recv(new_fd, recvBuf, size, 0);

    return ret;
}

/*
 * function : closeSocket
 *
 * description : close socket
 *
 *
 * intput : NULL
 *
 * output : NULL
 *
 * return : 0---SUCCESS; other ---- FAILED
 * */
int tcp_server::closeSocket()
{
    int ret = 0;

    close(new_fd);
	close(sockfd);

    return ret;
}
