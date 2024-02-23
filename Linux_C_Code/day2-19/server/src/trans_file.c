#include "process_pool.h"

#define DATA_LEN_MAX 1000

typedef struct data_packet_s {
    int length;
    char data[DATA_LEN_MAX];
}data_packet_t;

int trans_file(int netfd) {
    char filename[] = "testfile";

    data_packet_t packet;
    packet.length = strlen(filename);
    memcpy(packet.data, filename, packet.length);
    send(netfd, &packet, sizeof(packet.length) + packet.length, MSG_NOSIGNAL);

    struct stat stat_buf;
    int file_fd = open(filename, O_RDWR);
    ERROR_CHECK(file_fd, -1, "trans_file open");

    fstat(file_fd, &stat_buf);
    packet.length = sizeof(stat_buf.st_size);
    memcpy(packet.data, &stat_buf.st_size, packet.length);
    send(netfd, &packet, sizeof(packet.length) + packet.length, MSG_NOSIGNAL);

    printf("success send filename and size.\n");
#ifdef __linux__
    sendfile(netfd, file_fd, NULL, file_stat.st_size);
#elif defined __APPLE__
    sendfile(file_fd, netfd, 0, &stat_buf.st_size, NULL, 0);
#endif

    close(file_fd);
    return 0;
}
