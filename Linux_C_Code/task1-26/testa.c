#include <myselfc.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);

    int fdw = open(argv[1], O_WRONLY);

    printf("write open.\n");

    char buf[200] = {'a'};

    write(fdw, buf, 0);

    close(fdw);
    return 0;
}

