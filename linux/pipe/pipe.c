/*************************************************************************
	> File Name: pipe.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2017年08月04日 星期五 10时58分19秒
 ************************************************************************/
#include <stdio.h>  
#include <unistd.h>  
#include <sys/wait.h>  
#include <string.h>  
#include <stdlib.h>  
  
int main(void)  
{  
    pid_t pid;  
    int fd[2], i, n;  
    char buf[1024];  
  
    int ret = pipe(fd);  
    if(ret == -1){  
        perror("pipe error");  
        exit(1);  
    }  
  
    for(i = 0; i < 2; i++){  
        if((pid = fork()) == 0)  
            break;  
        else if(pid == -1){  
            perror("pipe error");  
            exit(1);  
        }  
    }  
  
    if (i == 0) {             
		printf("child 1\n");
        close(fd[1]);                 
        read(fd[0], buf, sizeof(buf));  
		printf("0 read:%s", buf);
    } else if(i == 1) {   
		printf("child 2\n");
        close(fd[1]);                 
        read(fd[0], buf, sizeof(buf)); 
		printf("1 read:%s", buf);
    } else {  
        close(fd[0]);       //父进程关闭写端,留读端读取数据
        n = write(fd[1], "hello world\n", strlen("hello wordl\n"));     //从管道中读数据
  
        for(i = 0; i < 2; i++)       //两个儿子wait两次  
            wait(NULL);  
    }  
  
    return 0;  
}  
