/*************************************************************************
	> File Name: dl.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2019年02月11日 星期一 17时37分09秒
 ************************************************************************/

#include<stdio.h>


#include <stdio.h>
#include <dlfcn.h>
 
int main(){
   void* handler = dlopen("./libdemo1.so",RTLD_LAZY);
//   int (*fun)(int,int) = dlsym(handler,"add");
//   int result = fun(34,25);
 
//   printf("the result of teo number is %d\n",result);
}
