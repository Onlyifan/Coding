#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include <time.h>

#define ERROR_CHECK(ret, num, msg)                                                                 \
    {                                                                                              \
        if (ret == num) {                                                                          \
            perror(msg);                                                                           \
            return -1;                                                                             \
        }                                                                                          \
    }

// 辅助函数：将kevent的udata转换为epoll_event.data
static inline void convert_kevent_to_epoll(struct kevent *kev, struct epoll_event *ev) {
    ev->events = kev->fflags;
    ev->data.ptr = kev->udata;
}

int epoll_create(int size) {
    int kq = kqueue( );
    if (kq == -1) {
        perror("kqueue");
        exit(EXIT_FAILURE);
    }
    return kq;
}

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event) {
    struct kevent kev;

    switch (op) {
    case EPOLL_CTL_ADD:
        EV_SET(&kev, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, event->data.ptr); // 使用用户数据
        if (event->events & EPOLLET) { // 边缘触发（Edge Triggered）
            kev.flags |= EV_CLEAR;     // 需要手动清理事件状态
        }
        break;
    case EPOLL_CTL_MOD:
        // 在kqueue中，修改监听事件通常需要先删除再添加
        epoll_ctl(epfd, EPOLL_CTL_DEL, fd, event);
        EV_SET(&kev, fd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, event->data.ptr);
        break;
    case EPOLL_CTL_DEL:
        EV_SET(&kev, fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        break;
    default:
        errno = EINVAL;
        return -1;
    }

    ERROR_CHECK(kevent(epfd, &kev, 1, NULL, 0, NULL), -1, "kevent");
    return 0;
}

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout) {
    struct timespec ts;
    if (timeout >= 0) {
        ts.tv_sec = timeout / 1000;
        ts.tv_nsec = (timeout % 1000) * 1000000;
    }

    int num_events =
        kevent(epfd, NULL, 0, (struct kevent *)events, maxevents, timeout >= 0 ? &ts : NULL);
    ERROR_CHECK(num_events, -1, "kevent");

    for (int i = 0; i < num_events; ++i) {
        convert_kevent_to_epoll((struct kevent *)&events[i], &events[i]);
    }

    return num_events;
}
