#ifndef PROCESS_POOL_H
#define PROCESS_POOL_H
#include <myselfc.h>

typedef enum worker_status_s{
    FREE,
    BUSY
}worker_status_t;

typedef struct worker_data_s {
    pid_t pid;
    worker_status_t status;
    uint32_t id;
    int sockpipefd;
}worker_data_t;

int worker_create(int worker_nums, worker_data_t *worker_data_arr);
int worker_loop(int sockpipefd);

int tcp_init(const char *ip, const char *port);
 
int epoll_add(int epfd, int fd, uint32_t event_data);
int epoll_del(int epfd, int fd);

int sendfd(int sockpipefd, int fd_to_send, bool exit_flag);
int recvfd(int sockpipefd, int *fd_to_send, bool *exit_flag);

int trans_file(int netfd);
#endif // PROCESS_POOL_H
