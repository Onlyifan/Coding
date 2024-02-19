#include <myselfc.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);

    int fdw = open(argv[1], O_RDWR);
    ERROR_CHECK(fdw, -1, "open with write");
    int fdr = open(argv[1], O_RDWR);
    ERROR_CHECK(fdr, -1, "open with read");

    int  count_read = 0;
    int  count_write = 0;
    char buf[4096] = {0};
    while(1){

        fd_set read_set, write_set;
        FD_ZERO(&read_set);
        FD_ZERO(&write_set);
        FD_SET(fdr, &read_set);
        FD_SET(fdw, &write_set);

        int ret = select(fdr + 1, &read_set, &write_set, NULL, NULL);

        if(FD_ISSET(fdw, &write_set)){
            write(fdw, buf, 4096);
            printf("valid fd = %d, count_write = %d.\n", ret, ++count_write);
        }

        if(FD_ISSET(fdr, &read_set)){
            read(fdr, buf, 1024);
            printf("valid fd = %d,  count_read = %d.\n", ret, ++count_read);
        }

        sleep(1);

    }

    return 0;
}

