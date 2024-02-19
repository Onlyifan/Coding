#include <myselfc.h>

#define BUF_SIZE 4096

int main(int argc, char* argv[]){
    ARGS_CHECK(argc, 2);

    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open");

    int name_size;
    ssize_t ret1 = read(fdr, &name_size, sizeof(int));
    ERROR_CHECK(ret1, -1, "read 1");

    char* name = (char*)malloc(name_size + 1);
    ssize_t ret2 = read(fdr, name, name_size);
    ERROR_CHECK(ret2, -1, "read 2");
    name[name_size] = '\0';

    char* path = (char*)calloc(1, 11 + name_size);
    strcat(strcpy(path, "saved_dir_"), name);

    int ret_mkdir = mkdir(path, 0777);
    ERROR_CHECK(ret_mkdir, -1, "mkdir");

    int ret_cd = chdir(path);
    ERROR_CHECK(ret_cd, -1, "chdir");

    int fdw = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
    ERROR_CHECK(fdw, -1, "open 2");
    
    off_t file_size;
    ssize_t ret3 = read(fdr, &file_size, sizeof(off_t));
    ERROR_CHECK(ret3, -1, "read 3");

    int ret4 = ftruncate(fdw, file_size);
    ERROR_CHECK(ret4, -1, "ftruncate");

    char buf[BUF_SIZE] = {0};
    while(1){
        memset(buf, 0, sizeof(buf));

        ssize_t count_read = read(fdr, buf, sizeof(buf));
        ERROR_CHECK(count_read, -1, "read");

        if(count_read == 0){
            break;
        }

        ssize_t count_write = write(fdw, buf, count_read);
        ERROR_CHECK(count_write, -1, "write");

    }

    close(fdw);
    free(name);
    close(fdr);
    return 0;
}
