/*
 * client.h
 *
 *  Created on: Nov 15, 2016
 *      Author: zp
 */

#ifndef JNI_TCP_CLIENT_H_
#define JNI_TCP_CLIENT_H_

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>

class tcp_client
{
public:
	tcp_client();
	~tcp_client();

	int initSocket(char *ip,int port);
	int recvSocket(char *recvBuf,int size);
	int sendSocket(char *sendData);
	int closeSocket();

	int sockfd;
private:

	struct sockaddr_in server_addr;
	struct hostent *host;
};


#endif /* JNI_TCP_CLIENT_H_ */
