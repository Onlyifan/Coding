#include <myselfc.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]){
    ARGS_CHECK(argc, 3);

    int fdw = open(argv[2], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open with write");
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open with read");

    printf("Program b is ready.\n");

    char buf[BUF_SIZE] = {0};


    fd_set read_set;
    while(1){
        memset(buf, 0, sizeof(buf));
        FD_ZERO(&read_set);
        FD_SET(STDIN_FILENO, &read_set);
        FD_SET(fdr, &read_set);
        select(fdr + 1, &read_set, NULL, NULL, NULL);

        if(FD_ISSET(STDIN_FILENO, &read_set)){
            ssize_t count_read = read(STDIN_FILENO, buf, sizeof(buf));
            ERROR_CHECK(count_read, -1, "read");

            if(count_read == 0){

                write(fdw, "b wanna close.\n", 14);

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

            if(count_read == 0){

                printf("Received close signal from a.\n");

                break;
            }
            printf("%s\n", buf);
        }

    }


    printf("Program b is closed.\n");
    return 0;
}
