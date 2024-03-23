#include <myselfc.h>

int main()
{
    printf("uid = %d\n", getuid());
    printf("gid = %d\n", getgid());
    printf("euid = %d\n", geteuid());
    printf("egid = %d\n", getegid());

    return 0;
}

