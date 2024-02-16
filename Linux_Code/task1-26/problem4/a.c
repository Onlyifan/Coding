#include <myselfc.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]){

    // ./main pipe filename
    ARGS_CHECK(argc, 3);

    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open");

    sleep(3);
    int name_size = strlen(argv[2]);
    write(fdw, &name_size, sizeof(int));
    write(fdw, argv[2], name_size);

    int fdr = open(argv[2], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open");

    off_t file_size = lseek(fdr, 0, SEEK_END);
    ERROR_CHECK(file_size, -1, "lseek");
    lseek(fdr, 0, SEEK_SET);
    write(fdw, &file_size, sizeof(off_t));

    char buf[BUF_SIZE] = {0};
    while(1){
        memset(buf, 0, sizeof(buf));

        ssize_t count_read = read(fdr, buf, sizeof(buf));
        ERROR_CHECK(count_read, -1, "read");

        if(count_read == 0){
            break;
        }

        write(fdw, buf, count_read);

    }

    close(fdr);
    close(fdw);
    return 0;
}
