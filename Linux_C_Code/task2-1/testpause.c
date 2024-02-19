#include <myselfc.h>


void handler(int signum){
    printf("start sleep, signum = %d\n", signum);

    sleep(5);

    printf("sleep over, signum = %d\n", signum);
}


int main(){

    signal(SIGINT, handler);
    signal(SIGQUIT, handler);



    pause();


    printf("program end.\n");
}
