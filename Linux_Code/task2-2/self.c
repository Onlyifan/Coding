#include <myselfc.h>

void *routine(void *arg){


    printf("child self = %lu\n", pthread_self());

    return NULL;
}



int main(int argc, char *argv[])
{
    pthread_t tid;

    pthread_create(&tid, NULL, routine, NULL);

    sleep(1);
    printf("main tid  = %lu\n", pthread_self());
    printf("tid = %lu\n", tid);

    
    
    return 0;
}

