#include <myselfc.h>

int main(int argc, char* argv[]){
    ARGS_CHECK(argc, 2);

    close(STDIN_FILENO);
    int fdr = open(argv[1], O_RDONLY);
    ERROR_CHECK(fdr, -1, "open");

    char buf[1024] = {0};
    scanf("%s", buf);
    //ssize_t sret = read(fdr,buf,sizeof(buf));
    //ERROR_CHECK(fdr, -1, "read");
    
    printf("%s\n", buf);

    for(int i = 0; i < 5; ++i){
        printf("Sleep 1s.\n");
        sleep(1);
    }

    close(fdr);
    return 0;
}
