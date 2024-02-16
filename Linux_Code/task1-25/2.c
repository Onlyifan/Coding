#include <myselfc.h>

#define BUFF_SIZE 512

int main(int argc, char* argv[])
{
    ARGS_CHECK(argc, 3);

    int fd1 = open(argv[1], O_RDONLY);
    ERROR_CHECK(fd1, -1, "open 1");
    int fd2 = open(argv[2], O_RDONLY);
    ERROR_CHECK(fd2, -1, "open 2");

    off_t file1_size = lseek(fd1, 0, SEEK_END);
    ERROR_CHECK(file1_size, -1, "lseek 1");
    off_t file2_size = lseek(fd2, 0, SEEK_END);
    ERROR_CHECK(file1_size, -1, "lseek 2");

    off_t ret1 = lseek(fd1, 0, SEEK_SET);
    ERROR_CHECK(ret1, -1, "lseek 1");
    off_t ret2 = lseek(fd2, 0, SEEK_SET);
    ERROR_CHECK(ret2, -1, "lseek 2");

    if(file1_size > file2_size){
        printf("Size of file1 was bigger.\n");

        return 0;
    }else if(file1_size < file2_size){    
        printf("Size of file2 was bigger.\n");
    
        return 0;
    }

    char* file1_buff[BUFF_SIZE] = {0};
    char* file2_buff[BUFF_SIZE] = {0};

    ssize_t bytes_read1, bytes_read2;
    while(1){

        bytes_read1 = read(fd1, file1_buff, sizeof(file1_buff));
        ERROR_CHECK(bytes_read1, -1, "read 1");
        bytes_read2 = read(fd2, file2_buff, sizeof(file2_buff));
        ERROR_CHECK(bytes_read2, -1, "read 2");

        if(bytes_read1 != bytes_read2){
            fprintf(stderr, "Error: bytes of read were different.\n");

            return -1;
        }

        while(bytes_read1 == 0){
            printf("These two files were the same.\n");

            return 0;
        }

        int result = memcmp(file1_buff, file2_buff, bytes_read1);

        if(result != 0){
            printf("These two files were different.\n");

            return 0;
        }

    }

    close(fd1);
    close(fd2);

    return 0;

}

