#include <myselfc.h>

typedef struct{
    int flag;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}shared_res_t;

void A(void){
    printf("Before A.\n");
    printf("After A.\n");
}

void B(void){
    printf("Before B.\n");
    printf("After B.\n");
}

void C(void){
    printf("Before C.\n");
    printf("After C.\n");
}

void *routine_t1(void *arg){
    shared_res_t *pshared_res = (shared_res_t *)arg;
    A();
    pthread_mutex_lock(&pshared_res->mutex);
    pshared_res->flag = 1;
    pthread_cond_signal(&pshared_res->cond);
    

    while(pshared_res->flag != 2){
        pthread_cond_wait(&pshared_res->cond, &pshared_res->mutex);
    }

    pthread_mutex_unlock(&pshared_res->mutex);
    C();

    pthread_exit(NULL);
}

void *routine_t2(void *arg){
    shared_res_t *pshared_res = (shared_res_t *)arg;
    pthread_mutex_lock(&pshared_res->mutex);
    while(pshared_res->flag != 1){
        pthread_cond_wait(&pshared_res->cond, &pshared_res->mutex);
    }    
    pthread_mutex_unlock(&pshared_res->mutex);
    B();

    pthread_mutex_lock(&pshared_res->mutex);
    pshared_res->flag = 2;

    pthread_cond_signal(&pshared_res->cond);
    pthread_mutex_unlock(&pshared_res->mutex);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    int ret;
    shared_res_t shared_res;
    shared_res.flag = 0;
    ret = pthread_mutex_init(&shared_res.mutex, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_mutex_init");
    ret = pthread_cond_init(&shared_res.cond, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_cond_init");
    pthread_t tid1, tid2;
    ret = pthread_create(&tid1, NULL, routine_t1, &shared_res);
    THREAD_ERROR_CHECK(ret, "pthread_create1");
    ret = pthread_create(&tid2, NULL, routine_t2, &shared_res);
    THREAD_ERROR_CHECK(ret, "pthread_create2");

    ret = pthread_join(tid1, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create1");
    ret = pthread_join(tid2, NULL);
    THREAD_ERROR_CHECK(ret, "pthread_create2");

    return 0;
}

