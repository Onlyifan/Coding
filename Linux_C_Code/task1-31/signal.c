#include <myselfc.h>

void handler(int signum){
    printf(" start handle signum = %d\n", signum);

    sleep(5);

    printf("  handle over signum = %d\n", signum);
}

int main(void){
    signal(SIGINT, handler);
    signal(SIGQUIT, handler);
    signal(SIGTSTP, handler);

    for(;;){

        sleep(5);
    }



    return 0;
}
