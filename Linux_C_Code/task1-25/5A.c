#include <myselfc.h>

int main (int argc, char* argv[]){
    ARGS_CHECK(argc, 2);

    printf("Helloworld\n");


    int backupfd = 10;
    int ret_dup2_1 = dup2(STDOUT_FILENO, backupfd);
    close(STDOUT_FILENO);
    ERROR_CHECK(ret_dup2_1, -1, "dup2");
    
    int fdw = open(argv[1], O_WRONLY);
    ERROR_CHECK(fdw, -1, "open");

    printf("HelloWorld\n");

    int ret_dup2_2 = dup2(backupfd, STDOUT_FILENO);
    ERROR_CHECK(ret_dup2_2, -1, "dup2");

    printf("HelloWorld\n");

    close(fdw);
    return 0;
   
}
