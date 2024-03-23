#include <myselfc.h>

#define BUFF_SIZE 4096

void *routine(void *arg){
    printf("child thread start running.\n");
    int fd = *(int *)arg;


    char buf[BUFF_SIZE] = {0};

    printf("child thread start write, fd = %d\n", fd);
    ssize_t ret = write(fd, buf, sizeof(buf));
    if(ret == -1){
        fprintf(stderr, "write");
    }

    printf("child thread end.\n");
    return NULL;
}



int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);

    int fd = open(argv[1], O_CREAT|O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open");

    pthread_t tid;
    int ret_thread_create = pthread_create(&tid, NULL, routine, (void *)&fd);
    THREAD_ERROR_CHECK(ret_thread_create, "pthread_create");
    printf("main thread sucess create child.\n");

    char buf[BUFF_SIZE] = {0};
    printf("main thread start read.\n");
    ssize_t read_count = read(fd, buf, sizeof(buf));
    ERROR_CHECK(read_count, -1, "read");
    printf("main thread read end.\n");


    sleep(1);

    return 0;
}
