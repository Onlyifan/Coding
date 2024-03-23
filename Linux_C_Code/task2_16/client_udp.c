#include <myselfc.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[])
{
    // ./client_udp 127.0.0.1 23333
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);

    // 第一次必须是客户端向服务端发消息
    sendto(sockfd, "hello", 5, 0,
            (struct sockaddr *)&server_addr, sizeof(server_addr));

    fd_set rdset;
    char buf[BUF_SIZE];
    while(1){
        memset(buf, 0, sizeof(buf));

        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO, &rdset);
        FD_SET(sockfd, &rdset);
        // 客户端不需要获取服务端的额外信息
        select(sockfd+1, &rdset, NULL, NULL, NULL);
        if(FD_ISSET(sockfd, &rdset)){
            ssize_t ret = recvfrom(sockfd, buf, sizeof(buf), 0, NULL, NULL);
            if(ret == 0){
                printf("receive a kick sign from server.\n");
                break;
            }
            printf("sret = %ld, buf = %s\n", ret, buf);
        }

        if(FD_ISSET(STDIN_FILENO,&rdset)){
            ssize_t ret = read(STDIN_FILENO, buf, sizeof(buf));
            if(ret == 0){
                sendto(sockfd,buf,0,0,
                        (struct sockaddr *)&server_addr,sizeof(server_addr));
                break;
            }
            sendto(sockfd, buf,
                    ret == 0? 0 : strlen(buf),
                    0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        }
    }

    close(sockfd);
    return 0;
}


