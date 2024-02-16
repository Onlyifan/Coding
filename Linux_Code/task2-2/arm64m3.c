#include <myselfc.h>

#define ADD_COUNT 20000000

int num = 0;

void *routine(void *arg){

    pthread_mutex_t *mutex = (pthread_mutex_t *)arg;
    for(int i = 0; i < ADD_COUNT; ++i){
        pthread_mutex_lock(mutex);
        ++num;
        pthread_mutex_unlock(mutex);
    }

    pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    
    struct timeval start_time, end_time;
    pthread_mutex_t mutex;
    int ret = pthread_mutex_init(&mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    pthread_t tid;


    gettimeofday(&start_time, NULL);
    pthread_create(&tid, NULL, routine, (void *)&mutex);
    
    for(int i = 0; i < ADD_COUNT; ++i){
        pthread_mutex_lock(&mutex);
        ++num;
        pthread_mutex_unlock(&mutex);
    }

    pthread_join(tid, NULL);
    gettimeofday(&end_time, NULL);

    int total_time = (end_time.tv_sec - start_time.tv_sec) * 1000000 + (end_time.tv_usec - start_time.tv_usec);
    printf("num = %u\n", num);
    printf("  total lock&unlock time = %dus\n", total_time);
    printf("average lock/unlock time = %lfns\n", (double)total_time * 1000 / 4 / ADD_COUNT);

    return 0;
}

