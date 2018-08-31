/*************************************************************************
	> File Name: test_overflow.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年01月04日 星期四 10时43分16秒
 ************************************************************************/

#include<stdio.h>
#include <stdio.h>
#include <string.h>

int check_password(char *password){
    int flag = 0;
    char buffer[20];
    strcpy(buffer, password);

    if(strcmp(buffer, "mypass") == 0){
        flag = 1;
    }
    if(strcmp(buffer, "yourpass") == 0){
        flag = 1;
    }
    return flag;
}

int main(int argc, char *argv[]){
    if(argc >= 2){
        if(check_password(argv[1])){
            printf("%s", "Access granted\n");
        }else{
            printf("%s", "Access denied\n");
        }
    }else{
        printf("%s", "Please enter password!\n");
    }
}
