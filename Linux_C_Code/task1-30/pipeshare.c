#include <myselfc.h>

#define BUFF_SIZE 4096

int main(void)
{
    int fds[2];

    int ret_pipe = pipe(fds);
    ERROR_CHECK(ret_pipe, -1, "pipe");
    if(fork()){
        close(fds[1]);
        char* buf[BUFF_SIZE] = {0};
        int count = 0;
        for(int i = 0; i < 10; ++i){
            int count_read = read(fds[0], buf, 2048);
            ERROR_CHECK(count_read, -1, "read");


            sleep(1);
            printf(" read size = %d,  read count = %d\n", count_read, ++count);
            if(i == 5){
                return 0;
            }
        }
    }
    else{
        close(fds[0]);
        char* buf[BUFF_SIZE] = {0};
        int count = 0;
        for(int i = 0; i < 10; ++i){
            int count_write = write(fds[1], buf, 4096);
            ERROR_CHECK(count_write, -1, "write");

            sleep(1);
            printf("write size = %d, write count = %d\n", count_write, ++count);
          //  if(i == 2){
          //      return 0;
          // }
        }

    }


    return 0;
}

