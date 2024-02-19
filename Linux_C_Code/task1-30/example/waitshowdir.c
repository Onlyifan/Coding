#include <myselfc.h>

int main(void){

    if(fork()){
        printf("wating son exec.\n");
        wait(NULL);
        printf("wait sucess.\n");
    }
    else{
        execl("showdir", "./showdir", ".", NULL);
    }

    return 0;

}
