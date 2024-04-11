#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <time.h>

#define KQUEUE_ERROR_CHECK(ret, num, msg)                                                          \
    {                                                                                              \
        if (ret == num) {                                                                          \
            perror(msg);                                                                           \
            exit(EXIT_FAILURE);                                                                    \
        }                                                                                          \
    }

int epoll_create(int size) {
    return kqueue( );
}
int epoll_create1(int flags) {
    return kqueue( );
}

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event) {
    struct kevent kev[2];

    if ((!event && op != EPOLL_CTL_DEL) ||
        (op != EPOLL_CTL_ADD && op != EPOLL_CTL_MOD && op != EPOLL_CTL_DEL)) {
        errno = EINVAL;
        return -1;
    }

    switch (op) {
    case EV_DELETE:
        EV_SET(&kev[0], fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        EV_SET(&kev[1], fd, EVFILT_WRITE, EV_DELETE, 0, 0, NULL);
        return kevent(epfd, kev, 2, NULL, 0, NULL);

    case EV_ADD:

        EV_SET(&kev[0], fd, EVFILT_READ, event->events & EPOLLIN ? EV_ADD : EV_DISABLE, 0, 0,
               event->data.ptr);
        EV_SET(&kev[1], fd, EVFILT_WRITE, event->events & EPOLLOUT ? EV_ADD : EV_DISABLE, 0, 0,
               event->data.ptr);
    }
    return kevent(epfd, kev, 2, NULL, 0, NULL);
}

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout) {
    struct timespec ts;
    if (timeout >= 0) {
        ts.tv_sec = timeout / 1000;
        ts.tv_nsec = (timeout % 1000) * 1000000;
    }

    int ready_events =
        kevent(epfd, NULL, 0, (struct kevent *)events, maxevents, timeout >= 0 ? &ts : NULL);

    for (int i = 0; i != ready_events; ++i) {
        if (((struct kevent *)(events + i))->filter == EVFILT_READ) {
            printf("in jiuxu\n");
            events[i].events = EPOLLIN;
        } else if (((struct kevent *)(events + i))->filter == EVFILT_WRITE) {
            printf("out jiuxu\n");
            events[i].events = EPOLLOUT;
        }
        printf("cont %d\n", events[i].events);

        (events + i)->data.ptr = ((struct kevent *)(events + i))->udata;
    }

    return ready_events;
}
