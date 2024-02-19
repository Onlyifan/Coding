#include <myselfc.h>

#define ADD_COUNT 10000000

int num = 0;

void *routine(void *arg){

    for(int i = 0; i < ADD_COUNT; ++i){
        ++num;
    }

    printf("child thread finished.\n");
    return NULL;
}


int main(void){

    pthread_t tid;

    pthread_create(&tid, NULL, routine, NULL);

    for(int i = 0; i < ADD_COUNT; ++i){
        ++num;
    }

    sleep(1);

    printf("num = %d\n", num);
}
