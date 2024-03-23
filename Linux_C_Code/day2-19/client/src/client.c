#include <myselfc.h>
#define DATA_LEN_MAX 1000

typedef struct data_packet_s {
    int length;
    char data[DATA_LEN_MAX];
}data_packet_t;

static int recvn(int sockfd, void *buf, long total){
    char *p = (char *)buf;
    long long cursize = 0;
    while(cursize < total){
        ssize_t sret = recv(sockfd, p + cursize, total - cursize, 0);
        if(sret == 0 || sret == -1){
            return -1;
        }
        cursize += sret;
    }
    return 0;
}

static int recvn_with_progress_bar(int sockfd, void *buf, long total_size) {
    char *p = (char *)buf;
    char fragment[4096] = {0};

    off_t last_size = 0;
    off_t current_size = 0;
    off_t slice = total_size / 1000;
    while (current_size < total_size) {
        sleep(1);
        ssize_t sret = recv(sockfd, fragment, ARR_LEN(fragment), 0);
        current_size += sret;
        if (current_size - last_size > slice) {
            printf("%.2f%% %.*s\r", 100.0f * current_size / total_size, (int)(10 * current_size / total_size), "##########");
            fflush(stdout);
        }

        last_size = current_size;
    }

    printf("100.00%% ##########\n");

    return 0;
}

int recvfile(int sockfd){
    data_packet_t packet;
    // 先收火车头，以知道车厢实际长度
    recvn(sockfd, &packet.length, sizeof(packet.length));
    recvn(sockfd, packet.data, packet.length);
    printf("suucess receive filename.\n");
    char filename[4096] = {0};
    memcpy(filename, packet.data, packet.length);
    recvn(sockfd, &packet.length, sizeof(packet.length));
    recvn(sockfd, packet.data, packet.length);
    printf("success receive filesize.\n");
    off_t filesize;
    memcpy(&filesize, packet.data, packet.length);

    printf("filesize = %lld\n", filesize);
    int fd = open(filename, O_CREAT|O_RDWR|O_TRUNC, 0666);
    ftruncate(fd, filesize); // 先修改文件大小
    char *p = (char *)mmap(NULL, filesize, PROT_READ|PROT_WRITE,MAP_SHARED, fd, 0);
    ERROR_CHECK(p, MAP_FAILED, "recvfile mmap");
    //recvn(sockfd, p, filesize);
    recvn_with_progress_bar(sockfd, p, filesize);
    munmap(p, filesize);
    close(fd);
    printf("success close fd.\n");
    return 0;
}



int main(int argc, char *argv[])
{
    // ./5_aqiang 192.168.72.128 1234
    // 192.168.72.128:1234 是服务端的ip端口
    ARGS_CHECK(argc, 3);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(atoi(argv[2]));
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    int ret = connect(sockfd,(struct sockaddr *)&serverAddr, sizeof(serverAddr));
    ERROR_CHECK(ret, -1, "main connect");
    recvfile(sockfd);

    return 0;
}

