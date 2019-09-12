#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int GetCpuCount() {
    return (int) sysconf(_SC_NPROCESSORS_ONLN);
}

void *thread_fun(void *param) {
    int i;
    while (1) {
        i = 0;
    }

    return NULL;
}

int main() {
    int cpu_num = 0;
    cpu_num = GetCpuCount();
    printf("The number of cpu is %d\n", cpu_num);

    pthread_t t[cpu_num];
    pthread_attr_t attr[cpu_num];

    for (int i = 0; i < cpu_num; i++) {
        pthread_attr_init(&attr[i]);

        cpu_set_t cpu_info;
        __CPU_ZERO_S(sizeof(cpu_set_t), &cpu_info);
        __CPU_SET_S(i, sizeof(cpu_set_t), &cpu_info);
        if (0 != pthread_attr_setaffinity_np(&attr[i], sizeof(cpu_set_t), &cpu_info)) {
            printf("set affinity failed");
            return -1;
        }

        if (0 != pthread_create(&t[i], &attr[i], thread_fun, NULL)) {
            printf("create thread 1 error\n");
            return -1;
        }

    }

    for (int i = 0; i < cpu_num; i++) {
        pthread_join(t[i], NULL);
    }

    return 0;
}
