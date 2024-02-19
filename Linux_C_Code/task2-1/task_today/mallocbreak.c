#include <myselfc.h>

void *threadFunc(void *arg){
    int *pVal = (int *)arg;
    printf("child, *pVal = %d\n", *pVal);
    ++*pVal;

    return NULL;
}

int main(void)
{

    int *num = (int *)malloc(sizeof(int));
    *num = 10086;
    pthread_t tid;
    pthread_create(&tid,NULL,threadFunc, num);
  //  usleep(1);
    free(num);
    usleep(500);
    return 0;
}
