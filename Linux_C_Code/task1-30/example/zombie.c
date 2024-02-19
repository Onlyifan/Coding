#include <myselfc.h>

int main(void){

    if(fork()){
        sleep(100);
    }
    else{
        ;
    }

    return 0;
}
