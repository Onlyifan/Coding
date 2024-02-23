#include <myselfc.h>
int main(int argc, char *argv[])
{
    // ./5_aqiang 192.168.72.128 1234
    // 192.168.72.128:1234 是服务端的ip端口
    ARGS_CHECK(argc,3);
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(sockfd,(struct sockaddr *)&serverAddr,sizeof(serverAddr));
    ERROR_CHECK(ret,-1,"connect");
    
    fd_set rdset;
    char buf[4096] = {0};

    printf("before into while.\n");
    while(1){
        FD_ZERO(&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        FD_SET(sockfd,&rdset);
        select(sockfd+1,&rdset,NULL,NULL,NULL);
        if(FD_ISSET(STDIN_FILENO,&rdset)){
            bzero(buf,sizeof(buf));
            read(STDIN_FILENO,buf,sizeof(buf));
            send(sockfd,buf,strlen(buf),0);
        }
        if(FD_ISSET(sockfd,&rdset)){
            bzero(buf,sizeof(buf));
            recv(sockfd,buf,sizeof(buf),0);
            printf("buf = %s\n", buf);
        }
    }

    return 0;
}

