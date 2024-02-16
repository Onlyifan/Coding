#include <myselfc.h>
#include <stdbool.h>

#define CIRCLE_TIMES 5

bool SIGN_A_FINISHED = false;

void *routine(void *arg){
    pthread_mutex_t *pmutex = (pthread_mutex_t *)arg;

    for(int i = 0; i < CIRCLE_TIMES; ++i){
        while(SIGN_A_FINISHED == false)
            ;
        pthread_mutex_lock(pmutex);

        printf("Before B!\n");
        sleep(3);
        printf("After B\n");
        SIGN_A_FINISHED = false;
        pthread_mutex_unlock(pmutex);
    }





    pthread_exit(NULL);
}




int main(int argc, char *argv[])
{

    pthread_mutex_t mutex;
    int ret = pthread_mutex_init(&mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    pthread_t tid;

    ret = pthread_create(&tid, NULL, routine, &mutex);
    THREAD_ERROR_CHECK(ret, "pthread_create");
    for(int i = 0; i < CIRCLE_TIMES; ++i){
        while(SIGN_A_FINISHED == true)
            ;
        pthread_mutex_lock(&mutex);

        printf("Before A!\n");
        sleep(3);
        printf("After A\n");

        SIGN_A_FINISHED = true;
        pthread_mutex_unlock(&mutex);

    }

    pthread_join(tid, NULL);


    return 0;
}

