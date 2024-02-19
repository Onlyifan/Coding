#include <myselfc.h>

typedef enum worker_status_s{
    FREE,
    BUSY
}worker_status_t;

typedef struct worker_data_s {
    pid_t pid;
    worker_status_t status;
    int id;
    int sockpipefd;
}worker_data_t;

int worker_create(int worker_nums, worker_data_t *worker_data_arr);
int worker_loop(int sockpipefd);

int tcp_init();

int epoll_add();
int epoll_delete();

int send_fd();
int recv_fd();
