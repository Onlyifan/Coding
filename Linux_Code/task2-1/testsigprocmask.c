#include <myselfc.h>


void handler(int signum){
    printf("start sleep, signum = %d\n", signum);

    sleep(5);

    printf("sleep over, signum = %d\n", signum);
}


int main(){

    sigset_t sign_set;

    sigemptyset(&sign_set);
    sigaddset(&sign_set, SIGINT);
    sigprocmask(SIG_SETMASK, &sign_set, NULL);

    sleep(5);

    sigemptyset(&sign_set);
    sigprocmask(SIG_SETMASK, &sign_set, NULL);

    pause();

    printf("program end.\n");
}
