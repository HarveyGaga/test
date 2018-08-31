/*
 * client.cpp
 *
 *  Created on: Nov 15, 2016
 *      Author: zp
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>


#include "client.h"


tcp_client::tcp_client()
{

}
tcp_client::~tcp_client()
{

}

/*
 * function : initSocket
 *
 * description : 1. open socket
 *               2. connect socket
 *
 * intput : ipaddr and portNum
 *
 * output : NULL
 *
 * return : 0 : SUCCESS ; other : FAILED
 * */
int tcp_client::initSocket(char *ip, int port)
{
	int ret = 0;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		return -1;
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr.s_addr  =  inet_addr(ip);
	if (connect(sockfd, (struct sockaddr *) (&server_addr),
			sizeof(struct sockaddr_in)) == -1)
	{
		fprintf(stderr, "Connect error:%s\n", strerror(errno));
		return -2;
	}
	return ret;
}
/*
 * function : recvSocket
 *
 * description : 1.recv data form socket
 *
 * intput :
 *
 * output : recv data
 *
 * return : 0 : SUCCESS ; other : FAILED
 * */
int tcp_client::recvSocket(char *recvBuf,int size)
{
	int ret = 0;

	ret = recv(sockfd, recvBuf, size, 0);

	return ret;
}

/*
 * function : sendSocket
 *
 * description : 1.socket send data
 *
 * intput : send data
 *
 * output : NULL
 *
 * return : 0 : SUCCESS ; other : FAILED
 * */
int tcp_client::sendSocket(char *sendData)
{
    int ret = 0;

    ret = send(sockfd, sendData, sizeof(sendData), 0);

    return ret;
}
/*
 * function : closeSocket
 *
 * description : close socket
 *
 * intput : NULL
 *
 * output : NULL
 *
 * return : 0 : SUCCESS ; other : FAILED
 * */
int tcp_client::closeSocket()
{
	int ret = 0;
	ret = close(sockfd);
	return ret;
}
