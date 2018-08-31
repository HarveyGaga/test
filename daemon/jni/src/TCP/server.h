/*
 * server.h
 *
 *  Created on: Nov 15, 2016
 *      Author: zp
 */

#ifndef JNI_TCP_SERVER_H_
#define JNI_TCP_SERVER_H_

#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>


class tcp_server
{
public:
	int initSocket(char *ip,int port);
	int sendSockset(char *sendData);
	int recvSocket(char *recvBuf,int size);
	int closeSocket();

private:
	int sockfd;
	int new_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
};




#endif /* JNI_TCP_SERVER_H_ */
