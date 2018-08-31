/*************************************************************************
	> File Name: main.c
	> Author: Harvey
	> Mail: hanwei@zhihuihutong.com 
	> Created Time: 2018年03月21日 星期三 16时52分06秒
 ************************************************************************/


#include <stdlib.h>  
#include <malloc.h>  
#include <string.h>  
#include <unistd.h>  
#include <pthread.h>
#if 0
void* test(void *arg)  
{  
    int *ptr = malloc(sizeof(int)*10);  
  
    ptr[10] = 7; // 内存越界  
  
    memcpy(ptr +1, ptr, 5); // 踩内存  
  
  
    free(ptr);   
    free(ptr);// 重复释放  
  
    int *p1;  
    *p1 = 1; // 非法指针  
}  
#endif

void* test(void *arg) {
	int a = *(int*)arg;
	printf("a = %d\n", a);
}


int main(int argc, char **argv)  
{  
	int a = 1000;
	while(a--) {
	pthread_t t_id[2];
	pthread_create(&t_id[0], NULL, test, &a);
	pthread_join(t_id[0], NULL);
	}

	return 0;  
}  
