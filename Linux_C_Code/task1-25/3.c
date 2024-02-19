#include <myselfc.h>


#define FILE_SIZE 1000000

int main(int argc, char* argv[])
{

    ARGS_CHECK(argc, 2);

    int fd = open(argv[1], O_RDWR | O_CREAT, 0666);
    ERROR_CHECK(fd, -1, "open");

    int ret_ftc = ftruncate(fd, FILE_SIZE);
    ERROR_CHECK(ret_ftc, -1, "ftruncate");

    char*p = (char*)mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE,
                         MAP_SHARED, fd, 0);
    ERROR_CHECK(p, MAP_FAILED, "mmap");

    memset(p, '1', FILE_SIZE); 


    munmap(p, FILE_SIZE);   
    close(fd);
    return 0;
}

