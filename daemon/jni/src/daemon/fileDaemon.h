/*
 * fileDaemon.h
 *
 *  Created on: Aug 5, 2016
 *      Author: zp
 */

#ifndef DAEMON_FILEDAEMON_H_
#define DAEMON_FILEDAEMON_H_


#define FILE_TYPE  0x08
#define LINK_TYPE  0x0A
#define DIR_TYPE   0x04


#define SRC_PATH_ERROR     0xFFFFFFF0
#define SRC_FILE_ERROR     0xFFFFFFF1


class fileDaemon
{
public:
	fileDaemon();
	virtual ~fileDaemon();

	int createDir(const char *sPathName);
	int fileExists(const char *filePath,const char *fileName);
	int deletFile(const char *filePath,const char *fileName);
	int readFileName(const char *filePath,char (*fileName)[256],int *fileNume);
	int judgePicFormat(char *srcFile, char *desFile);
	int judgeVidoFormat(char *srcFile, char *desFile);
	int matchPic(const char *srcPath,const char *desPath);
	int checkFilePic(const char *origiPath,const char *thumbPath);

	int matchVido(const char *srcPath,const char *desPath);
	int checkFileVido(const char *origiPath,const char *thumbPath);

private:
	const int picOrigNameLen = 22;
	const int picThumbNameLen = 28;
	const int vidoOrigNameLen = 19;
	const int vidoThumbNameLen = 25;
};


#endif /* DAEMON_FILEDAEMON_H_ */
