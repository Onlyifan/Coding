#include <myselfc.h>

void *routine(void *arg){


    int count = 0;

    while(1){
    printf("%d\n", ++count);
    pthread_testcancel();

    }
    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    pthread_t tid;

    pthread_create(&tid, NULL,routine, NULL);

    void *ret;
    printf("tid = %lu\n", tid);

    usleep(1);

    pthread_cancel(tid);
    pthread_join(tid, &ret);

    printf("tid = %lu, ret = %ld\n", tid, (long)ret);

    return 0;
}

