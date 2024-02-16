#include <myselfc.h>

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 2);

    int fdw = open(argv[1], O_RDONLY);

    printf("read open.\n");

    char buf[200] = {'8'};

    while(1)
    read(fdw, buf, 200);
printf("%c", buf[0]);
    return 0;
}

