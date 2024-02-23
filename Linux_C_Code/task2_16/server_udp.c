#include <myselfc.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    ARGS_CHECK(argc, 3);
    // ./server_udp 0.0.0.0 23333 
    int sockfd = socket(AF_INET, SOCK_DGRAM,0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = bind(sockfd, (struct sockaddr* )&server_addr, sizeof(server_addr));
    ERROR_CHECK(ret, -1, "bind");

    struct sockaddr_in client_addr;
    // socklen必须提前定义
    socklen_t socklen = sizeof(client_addr);
    char buf[BUF_SIZE] = {0};
    recvfrom(sockfd, buf, ARR_LEN(buf), 0, (struct sockaddr *)&client_addr, &socklen); // socklen的设置和accept一样
    printf("buf = %s, client_ip = %s, client_port = %d\n", 
            buf, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    fd_set rdset;
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sockfd, &rdset);
        select(sockfd + 1, &rdset, NULL, NULL, NULL);

        memset(buf, 0, sizeof(buf));

        if(FD_ISSET(sockfd, &rdset)){
            // 这里不需要再获取客户端额外信息
            ssize_t sret = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
            if(sret == 0){
                printf("client send a exit sign.\n");
                break;
            }
            printf("sret = %ld, buf = %s\n", sret, buf);
        }

        if(FD_ISSET(STDIN_FILENO, &rdset)){
            ssize_t ret = read(STDIN_FILENO, buf, sizeof(buf));
            ERROR_CHECK(ret, -1, "read");
            sendto(sockfd, buf,
                    ret == 0? 0 : strlen(buf), 0,
                    (struct sockaddr *)&client_addr,sizeof(client_addr));
        }
    }

    close(sockfd);
    return 0;
}


