#include <arpa/inet.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>


#define SERV_PORT 8888


int main( ) {

    int listenfd, connfd, sockfd;
    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len;
    int ret, maxfd, maxi, i, j, nready, nByte;
    fd_set rset, allset;


    int client[FD_SETSIZE];

    char buf[BUFSIZ], str[BUFSIZ];

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd) {

        perror("socket error");
        exit(-1);
    }

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    int opt2 = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt2, sizeof(opt2));

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(SERV_PORT);

    ret = bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (-1 == ret) {
        perror("bind error");
        exit(-1);
    }

    ret = listen(listenfd, 50);
    if (-1 == ret) {
        //
    }

    maxfd = listenfd;
    maxi = -1;

    for (i = 0; i != FD_SETSIZE; ++i) {
        client[i] = -1;
    }
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);

    for (;;) {
        rset = allset;

        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nready < 0)
            ;

        if (FD_ISSET(listenfd, &rset)) {
            clie_addr_len = sizeof(clie_addr);
            connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
            if (-1 == connfd)
                ;

            printf("client ip %s port %d\n",
                   inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, str, sizeof(str)),
                   ntohs(clie_addr.sin_port));

            for (int i = 0; i != FD_SETSIZE; ++i) {
                if (client[i] < 0) {
                    client[i] = connfd;
                    break;
                }
            }

            if (i == FD_SETSIZE) {
                fputs("two many clients\n", stderr);
                return -1;
            }

            if (i > maxi) {
                maxi = i;
            }

            FD_SET(connfd, &allset);

            if (connfd > maxfd) {
                maxfd = connfd;
            }

            if (--nready == 0) {
                continue;
            }
        }

        for (int i = 0; i <= maxi; ++i) {
            if ((sockfd = client[i]) < 0) {
                continue;
            }

            if (FD_ISSET(sockfd, &rset)) {
                if ((nByte = read(sockfd, buf, sizeof(buf))) == 0) {
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                } else if (nByte > 0) {
                    write(sockfd, buf, nByte);
                    write(STDOUT_FILENO, buf, nByte);
                } else {
                    return -1;
                }

                if (--nready == 0) {
                    break;
                }
            }
        }
    }

    close(listenfd);
    close(connfd);

    for (int i = 0; i <= maxi; ++i) {
        if ((sockfd = client[i]) < 0) {
            continue;
        }

        close(sockfd);
    }


    return 0;
}
