#include <arpa/inet.h>
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// #define SERV_IP "127.0.0.1"
// INADDR_LOOPBACK;
#define SERV_PORT 8888


int main( ) {
    int nByte;

    int connfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == connfd) {
        perror("socket");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    // inet_pton(AF_INET, INADDR_LOOPBACK, &server_addr.sin_addr.s_addr);
    server_addr.sin_port = htons(SERV_PORT);

    int ret = connect(connfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (ret) {
        perror("connect");
        return -1;
    }

    for (;;) {
        char buf[BUFSIZ] = {0};

        fgets(buf, sizeof(buf), stdin);
        write(connfd, buf, sizeof(buf));

        memset(buf, 0, sizeof(buf));

        nByte = read(connfd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, nByte);
    }

    close(connfd);
    return 0;
}
