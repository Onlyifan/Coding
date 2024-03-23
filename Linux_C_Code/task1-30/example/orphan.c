#include <myselfc.h>

int main(void)
{
    if(fork()){
        printf("I am parent, my pid = %d, my ppid = %d\n", getpid(), getppid());
        sleep(1);
        return 0;
    }
    else{
        printf("I am son, my pid = %d, my getppid = %d\n", getpid(), getppid());
        sleep(2);
        
        printf("I am orphan, my pid = %d, my ppid = %d\n", getpid(), getppid());
    }

    return 0;
}

