#include <myselfc.h>

int main(int argc, char* argv[]){
    ARGS_CHECK(argc, 2);
    DIR* dir = opendir(argv[1]);
    ERROR_CHECK(dir, NULL, "opendir");


    struct dirent *pdirent;
    while((pdirent = readdir(dir)) != NULL){

        printf("%s\n", pdirent->d_name);
    }

    closedir(dir);
    return 0;
}
