#include <myselfc.h>

#define BUFF_SIZE 4096

void *routine(void *arg){
    printf("child thread start running.\n");

    sleep(3);
    printf("child thread sleep over.\n");
    int fd = *(int *)arg;

    printf("child thread start write, fd = %d\n", fd);
    ssize_t ret = write(fd, "child", 5);
    if(ret == -1){
        fprintf(stderr, "write error!\n");
    }
    else{

        printf("child thread write over.\n");
    }

    printf("child thread end.\n");
    return NULL;
}



int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 2);

    int fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0666);
    ERROR_CHECK(fd, -1, "open");

    pthread_t tid;
    int ret_thread_create = pthread_create(&tid, NULL, routine, (void *)&fd);
    THREAD_ERROR_CHECK(ret_thread_create, "pthread_create");
    printf("main thread sucess create child.\n");

    printf("main thread was going to close fd after sleep 3s.\n");
    sleep(3);
    usleep(1);
    ssize_t ret_write = write(fd, "main", 4);
    ERROR_CHECK(ret_write, -1, "write");
    printf("main thread write over.\n");
    printf("main thread was going to close fd.\n");
    int ret_close = close(fd);
    ERROR_CHECK(fd, -1, "close");
    printf("main thread success close fd = %d\n", fd);
    char buf[BUFF_SIZE] = {0};
    printf("main thread start read.\n");
    ssize_t read_count = read(fd, buf, sizeof(buf));
    ERROR_CHECK(read_count, -1, "read");
    printf("main thread read end.\n");


    sleep(1);

    return 0;
}
