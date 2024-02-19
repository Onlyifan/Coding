#include <myselfc.h>

int num = 0;
void *threadFunc(void *arg){
    pthread_mutex_t mutex  = *((pthread_mutex_t *)arg);
    for(int i = 0;i < 20000000; ++i){
        pthread_mutex_lock(&mutex);
        ++num;
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}
int main()
{
    int ret;
    pthread_t tid;
    pthread_mutex_t mutex;
    ret = pthread_mutex_init(&mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    struct timeval begTime,endTime;
    gettimeofday(&begTime,NULL);
    ret = pthread_create(&tid,NULL,threadFunc,(void *)&mutex);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    for(int i = 0;i < 20000000; ++i){
        pthread_mutex_lock(&mutex);
        ++num;
        pthread_mutex_unlock(&mutex);
    }
    ret = pthread_join(tid,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    gettimeofday(&endTime,NULL);
    long avgtime = ((endTime.tv_sec - begTime.tv_sec )* 1000000 +
                    (endTime.tv_usec - begTime.tv_usec));
    printf("avg lock/unlock time = %ld\n",avgtime);
    printf("val = %d\n", num);
    ret = pthread_mutex_destroy(&mutex);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_destroy");
    return 0;
}
