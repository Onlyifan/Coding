#include <myselfc.h>

#define BUF_SIZE 4096
#define TIMEVAL_LIMIT 10
int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);

    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open with read");
    int fdw = open(argv[2], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open with write");

    printf("Program a is ready.\n");

    char buf[BUF_SIZE] = {0};

    struct timeval timeval_s;
    time_t time_current = time(NULL);

    fd_set read_set;

    while(1){

        timeval_s.tv_sec = 1;
        timeval_s.tv_usec = 0;
        memset(buf, 0, sizeof(buf));
        FD_ZERO(&read_set);
        FD_SET(STDIN_FILENO, &read_set);
        FD_SET(fdr, &read_set);

        if(time(NULL) - time_current > TIMEVAL_LIMIT){
            printf("Close chat due to b was inactive.\n");

            break;
        }

        select(fdw + 1, &read_set, NULL, NULL, &timeval_s);
        if(FD_ISSET(STDIN_FILENO, &read_set)){
            ssize_t count_read = read(STDIN_FILENO, buf, sizeof(buf));
            ERROR_CHECK(count_read, -1, "read");

            if(count_read == 0){

                write(fdw, "a wanna close.\n", 14);

                break;
            }

            time_t current_time = time(NULL);
            char* time_str = ctime(&current_time);
            write(fdw, time_str, strlen(time_str));
            write(fdw, buf, count_read);

        }
        if(FD_ISSET(fdr, &read_set)){
            int count_read = read(fdr, buf, sizeof(buf));
            ERROR_CHECK(count_read, -1, "read");

            time_current = time(NULL);

            if(count_read == 0){

                printf("Received close signal from b.\n");

                break;
            }
            printf("%s\n", buf);
        }

    }


    printf("Program a has closed.\n");
    return 0;
}
