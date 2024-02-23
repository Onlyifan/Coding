#include "process_pool.h"

int epoll_add(int epfd, int fd, uint32_t event_data){
    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.u32 = event_data;
    epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);

    return 0;
}

int epoll_del(int epfd, int fd){
    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
    return 0;
}
