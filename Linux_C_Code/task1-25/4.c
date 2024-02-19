#include <myselfc.h>

int main(int argc, char* argv[])
{
    ARGS_CHECK(argc, 2);

    int fd = open(argv[1], O_RDWR);
    ERROR_CHECK(fd, -1, "open");

    off_t file_size = lseek(fd, 0, SEEK_END);
    ERROR_CHECK(file_size, -1, "lseek 1");

    off_t ret = lseek(fd, 0, SEEK_SET);
    ERROR_CHECK(ret, -1, "lseek 2");

    char* file_p = (char*)mmap(NULL, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    ERROR_CHECK(file_p, MAP_FAILED, "mmap");

    for(int i = 0; i< file_size; ++i){
        char current = file_p[i];
        if(islower(current)){
            file_p[i] = toupper(current);

        }else if(ispunct(current)){
            file_p[i] = ' ';
        }

    }



    munmap(file_p, file_size);
    close(fd);
    return 0;
}

