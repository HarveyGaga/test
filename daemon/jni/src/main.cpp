/*
 * main.cpp
 *
 *  Created on: Jun 2, 2016
 *      Author: root
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <algorithm>
#include<signal.h>
#include <iostream>
#include <sys/statfs.h>
#include <dirent.h>
#include <errno.h>
#include <pthread.h>


#include "client.h"
#include "fileDaemon.h"


static const char softwareVersion[] = "1.01";
char section_name[64] = "daemonfinger";

static int runFlag = 1;

static  char ipaddr[64] = "192.168.1.1";
static  int port = 7090;


void ctrlhandler(int a)
{
	printf("you have press ctrl+c \n");
    runFlag = 0;
	exit(0);
}
static void parse_command(char argc, char *argv[])
{
	int option;
	char str_date[32];
	char str_time[32];
	int pathLen = 0;
	int len = 128;
	char *path_end;
	char processName[32];
	char processdir[128];
	char tmpProcessdir[128];
	char section_name[32];



	while ((option = getopt(argc, argv, ":vi:")) != -1) //getopt define in unistd.h
	{
		pathLen = readlink("/proc/self/exe", tmpProcessdir, len);
		if (pathLen <= 0)
		{
			printf("get exe name failed ... \n");

			return;
		}
		memcpy(processdir, tmpProcessdir, pathLen);
		path_end = strrchr(processdir, '/');
		if (path_end == NULL)
		{
			printf("exe name : NULL ... \n");
		}
		memcpy(processName, (path_end + 1), strlen(path_end));

		switch (option)
		{
		case 'i':
			sprintf(section_name, "%s", optarg);
			break;
		case 'v':
			sprintf(str_date, "%s", __DATE__);
			sprintf(str_time, "%s", __TIME__);
			printf("%s version V%s\ncompile date:\n%s %s\n", processName,
					softwareVersion, str_date, str_time);
			exit(1);
			break;
		case ':':
			fprintf(stderr, "Error: -%c without argument\n", optopt);
			exit(1);
			break;
		case '?':
			fprintf(stderr, "Error: Unknown argument %c\n", optopt);
			exit(1);
			break;
		default:
			exit(1);
		}
	}
}


void *tcp_send(void *paras)
{
	char sendData[64]="daemon";
	tcp_client *client = (tcp_client *)paras;

	while(runFlag)
	{
		client->sendSocket(sendData);

		sleep(1);
	}
}
void * checkFile(void *)
{
	fileDaemon fileManager;
	char mnt_pic_path[128] = "/mnt/media_rw/pic";
	char mnt_video_path[128] = "/mnt/media_rw/video";
	char data_pic_path[128] = "/data/thumbnails/pic";
	char data_video_path[128] = "/data/thumbnails/video";

	while (runFlag)
	{
			fileManager.checkFilePic(mnt_pic_path, data_pic_path);
			fileManager.checkFileVido(mnt_video_path, data_video_path);
			sleep(10);
	}
}

void restart_pid()
{
    int ret = 0;

//    if(strcmp(pidName,"uav_cameraservice") == 0)
    {
    	ret = system("busybox pidof setWifi");
    	if(ret != 0)
    	{
    		system("/data/wifi/setWifi &");
    	}

//    	printf("restart app ... \n");
//    	ret = system("busybox pidof lc_app_update");
//    	if(ret != 0)
//    	{
//    		system("/data/update/APP/lc_app_update &");
//    	}
//
//
//
//    	printf("restart ota ... \n");
//    	ret = system("busybox pidof lc_ota_update");
//    	if(ret != 0)
//    	{
//    		system("/data/update/OTA/lc_ota_update &");
//    	}



    	ret = system("busybox pidof ctlengine");
    	if(ret != 0)
    	{
    		system("/data/current/ce/ctlengine &");
    	}


    	ret = system("busybox pidof uav_cameraservice");
    	if(ret != 0)
    	{
    		system("/data/current/cs/uav_cameraservice &");
    	}

    	ret = system("busybox pidof http_server");
    	if(ret != 0)
    	{
    	      char buf[80];
    	      getcwd(buf,sizeof(buf));

    		chdir("/data/current/http_server");
    		system("pwd");
    		system("./http_server &");
    		chdir(buf);

    	}

    	ret = system("busybox pidof usb_opticflow");
    	if(ret != 0)
    	{
    		system("/data/current/opticFlow/usb_opticflow &");
    	}


    }

}

int main(int argc, char *argv[])
{
	int ret = 0;

	pthread_t recvId;
	pthread_t sendId;
	pthread_t checkFileId;

	 /*SIGINI == 2; ctrl + c == kill -2 process*/
	signal(SIGINT,ctrlhandler);
    parse_command(argc,argv);

	tcp_client client;

	client.initSocket(ipaddr,port);


//	pthread_create(&sendId,NULL,tcp_send,&client);

//	pthread_create(&recvId,NULL,(void *)tcp_recv,NULL);


    pthread_create(&checkFileId,NULL,checkFile,NULL);


	while (runFlag)
	{
		restart_pid();
		sleep(10);
	}

	client.closeSocket();
    pthread_join(checkFileId,NULL);
//	pthread_join(sendId,NULL);

	return ret;
}
