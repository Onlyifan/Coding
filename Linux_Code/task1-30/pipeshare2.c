#include <myselfc.h>

#define BUFF_SIZE 4096

int main(void)
{
    int pds[2];

    int ret_pipe = pipe(pds);
    ERROR_CHECK(ret_pipe, -1, "pipe");
    if(fork()){
        char* buf[BUFF_SIZE] = {0};
        int count = 0;
        while(1){
            int count_write = write(pds[1], buf, 4096);
            ERROR_CHECK(count_write, -1, "write");

            sleep(1);
            printf("write size = %d, write count = %d\n", count_write, ++count);
        }
    }
    else{
        char* buf[BUFF_SIZE] = {0};
        int count = 0;
        while(1){
            int count_read = read(pds[0], buf, 2048);
            ERROR_CHECK(count_read, -1, "read");
            
            sleep(1);
            printf(" read size = %d,  read count = %d\n", count_read, ++count);
        }

    }


    return 0;
}

