/*
 * fileDaemon.cpp
 *
 *  Created on: Aug 5, 2016
 *      Author: zp
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <algorithm>

#include "fileDaemon.h"

fileDaemon::fileDaemon()
{
	// TODO Auto-generated constructor stub
}

fileDaemon::~fileDaemon()
{
	// TODO Auto-generated destructor stub
}

int fileDaemon::createDir(const char *sPathName)
{
	char dirName[256];
	int i;
	int len;

	strcpy(dirName, sPathName);
	len = strlen(dirName);
	if (dirName[len - 1] != '/')
	{
		strcat(dirName, "/");
	}

	for (i = 1; i <= len; i++)
	{
		if (dirName[i] == '/')
		{
			dirName[i] = 0;
			if (access(dirName, 0) != 0)
			{
				if (mkdir(dirName, 0755) == -1)
				{
					perror("mkdir   error");
					return -1;
				}
			}
			dirName[i] = '/';
		}
	}

	return 0;
}

int fileDaemon::readFileName(const char *filePath, char fileName[][256],
		int *fileNume)
{
	int ret = 0;
	int i = 0;
	DIR *dir;
	char dirName[256][256];
	struct dirent *ptr;

	dir = opendir(filePath);

	while ((ptr = readdir(dir)) != NULL)
	{
		if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0))
		{
			continue;
		}
		else if (ptr->d_type == FILE_TYPE)
		{
//			printf("file name : %s \n", ptr->d_name);
			strcpy(dirName[i], ptr->d_name);
			strcpy(fileName[i], dirName[i]);
			i++;
		}
	}
	*fileNume = i;
	closedir(dir);
	return ret;
}

int fileDaemon::fileExists(const char *filePath, const char *fileName)
{
	int ret = 0;
	char file[128];

	sprintf(file, "%s/%s", filePath, fileName);

	ret = access(file, F_OK);

	return ret;
}
int fileDaemon::deletFile(const char *filePath, const char *fileName)
{
	int ret = 0;
	char file[128];

	sprintf(file, "%s/%s", filePath, fileName);
	printf("delet file : %s \n", file);
	ret = remove(file);

	return ret;
}
int fileDaemon::judgePicFormat(char *srcFile, char *desFile)
{
	int ret = 0;
	int nameLen = 0;
	char *tmpName;
	char head20[2];

	nameLen = strlen(srcFile);
	/*1. judge filename len == 22*/
	if (nameLen == picOrigNameLen)
	{
		tmpName = strrchr(srcFile, '.');
		/*2. judge filename the suffix .jpg or not*/
		ret = strcmp(tmpName, ".jpg");
		if (ret != 0)
		{
			return -1;
		}
		else
		{
			/*3. judge filename head "20xxxxx" or not*/
			memcpy(head20, srcFile, 2);
			if (strncmp(head20, "20", 2) != 0)
			{
				return -2;
			}
			else
			{
				/*4. judge filename 9th "_" or not*/
				if (srcFile[8] != '_')
				{
					return -3;
				}
				else
				{

					strncpy(desFile, srcFile, 18);
					strcat(desFile, "_thumb.jpg");
				}
			}
		}
	}
	else if (nameLen == picThumbNameLen)
	{
		tmpName = strrchr(srcFile, '_');
		ret = strcmp(tmpName, "_thumb.jpg");
		if (ret != 0)
		{
			return -4;
		}
		else
		{
			strncpy(desFile, srcFile, 18);
			strcat(desFile, ".jpg");
		}
	}
	else
	{
		return -5;
	}
	return ret;
}
int fileDaemon::judgeVidoFormat(char *srcFile, char *desFile)
{
	int ret = 0;
	int nameLen = 0;
	char *tmpName;
	char head20[2];

	nameLen = strlen(srcFile);
	/*1. judge filename len == 19*/
	if (nameLen == vidoOrigNameLen)
	{
		tmpName = strrchr(srcFile, '.');
		/*2. judge filename the suffix .jpg or not*/
		ret = strcmp(tmpName, ".mp4");
		if (ret != 0)
		{
			return -1;
		}
		else
		{
			/*3. judge filename head "20xxxxx" or not*/
			memcpy(head20, srcFile, 2);
			if (strncmp(head20, "20", 2) != 0)
			{
				return -2;
			}
			else
			{
				/*4. judge filename 9th "_" or not*/
				if (srcFile[8] != '_')
				{
					return -3;
				}
				else
				{

					strncpy(desFile, srcFile, 15);
					strcat(desFile, "_thumb.jpg");
				}
			}
		}
	}
	else if (nameLen == vidoThumbNameLen)
	{
		tmpName = strrchr(srcFile, '_');
		ret = strcmp(tmpName, "_thumb.jpg");
		if (ret != 0)
		{
			return -4;
		}
		else
		{
			strncpy(desFile, srcFile, 15);
			strcat(desFile, ".mp4");
		}
	}
	else
	{
		return -5;
	}
	return ret;
}

int fileDaemon::matchPic(const char *srcPath, const char *desPath)
{
	int ret = 0;
	int i = 0;
	int fileNume = 0;
	char srcfileName[256][256];
	char desFileName[256][256];

	ret = createDir(srcPath);
	if (ret != 0)
	{
		ret = SRC_PATH_ERROR;
	}
	else
	{
		ret = readFileName(srcPath, srcfileName, &fileNume);
		if (ret != 0)
		{
			ret = SRC_FILE_ERROR;
		}
		else
		{
			for (i = 0; i < fileNume; i++)
			{
				memset(desFileName[i], 0, sizeof(desFileName[i]));
				/*judge file match pic format*/
				ret = judgePicFormat(srcfileName[i], desFileName[i]);
				if (ret != 0)
				{
					return ret;
				}
				else
				{
					ret = createDir(desPath);
					if (ret == 0)
					{
						ret = fileExists(desPath, desFileName[i]);
						if (ret != 0)
						{
							sleep(2);
							ret = fileExists(desPath, desFileName[i]);
							if (ret != 0)
							{
								ret = deletFile(srcPath, srcfileName[i]);
							}
						}
					}
				}
				/*clean 256 byte , must add*/
				memset(srcfileName[i], 0, 256);
				memset(desFileName[i], 0, 256);
			}
		}
	}

	return ret;
}

int fileDaemon::checkFilePic(const char *origiPath, const char *thumbPath)
{
	int ret = 0;
	ret = matchPic(origiPath, thumbPath);
	if (ret == 0)
	{
		ret = matchPic(thumbPath, origiPath);
	}
	return ret;
}

int fileDaemon::matchVido(const char *srcPath, const char *desPath)
{
	int ret = 0;
	int i = 0;
	int fileNume = 0;
	char srcfileName[256][256];
	char desFileName[256][256];

	ret = createDir(srcPath);
	if (ret != 0)
	{
		ret = SRC_PATH_ERROR;
	}
	else
	{
		ret = readFileName(srcPath, srcfileName, &fileNume);
		if (ret != 0)
		{
			ret = SRC_FILE_ERROR;
		}
		else
		{
			for (i = 0; i < fileNume; i++)
			{
				/*judge file format*/
				ret = judgeVidoFormat(srcfileName[i], desFileName[i]);
				if (ret != 0)
				{
					return ret;
				}
				else
				{
					/*find file exist or not*/
					ret = createDir(desPath);
					if (ret == 0)
					{
						ret = fileExists(desPath, desFileName[i]);
						if (ret != 0)
						{
							sleep(2);
							ret = fileExists(desPath, desFileName[i]);
							if (ret != 0)
							{
								ret = deletFile(srcPath, srcfileName[i]);
							}
						}
					}
				}
				/*clean 256 byte , must add*/
				memset(srcfileName[i], 0, 256);
				memset(desFileName[i], 0, 256);
			}
		}
	}

	return ret;
}

int fileDaemon::checkFileVido(const char *origiPath, const char *thumbPath)
{
	int ret = 0;
	ret = matchVido(origiPath, thumbPath);
	if (ret == 0)
	{
		ret = matchVido(thumbPath, origiPath);
	}
	return ret;
}

