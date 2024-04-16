#ifndef _SYS_EPOLL_H_
#define _SYS_EPOLL_H_


#include <sys/event.h>


// Epoll events
#define EPOLLIN 0x001
#define EPOLLPRI 0x002
#define EPOLLOUT 0x004
#define EPOLLRDNORM 0x040
#define EPOLLRDBAND 0x080
#define EPOLLWRNORM 0x100
#define EPOLLWRBAND 0x200
#define EPOLLMSG 0x400
#define EPOLLERR 0x008
#define EPOLLHUP 0x010
#define EPOLLRDHUP 0x2000
#define EPOLLEXCLUSIVE 1u << 28
#define EPOLLWAKEUP 1u << 29
#define EPOLLONESHOT 1u << 30
#define EPOLLET 1u << 31

// Epoll_ctl operations
#define EPOLL_CTL_ADD 1
#define EPOLL_CTL_DEL 2
#define EPOLL_CTL_MOD 3

typedef union epoll_data {
    void    *ptr; /* Pointer to user data */
    int      fd;  /* File descriptor (for level-triggered I/O) */
    uint32_t u32; /* Generic 32-bit data type */
    uint64_t u64; /* Generic 64-bit data type */
    char     padding[sizeof(struct kevent) - sizeof(uint32_t)];
} epoll_data_t;

struct epoll_event {
    uint32_t     events; /* Epoll events */
    epoll_data_t data;   /* User data variable */
};

#ifdef __cplusplus
extern "C" {
#endif

extern int epoll_create(int size);
extern int epoll_create1(int flags);
extern int epoll_ctl(int kq, int op, int fd, struct epoll_event *event);
extern int epoll_wait(int kq, struct epoll_event *events, int max_events, int timeout);

#ifdef __cplusplus
}
#endif


#endif // _SYS_EPOLL_H_
