#ifndef MYSELFC_H
#define MYSELFC_H

#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/ipc.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/shm.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#ifdef __linux__
#include <sys/sendfile.h>
#endif // __linux__


#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARGS_CHECK(argc, num)                                                                      \
    {                                                                                              \
        if (argc != num) {                                                                         \
            fprintf(stderr, "args error!\n");                                                      \
            return -1;                                                                             \
        }                                                                                          \
    }
#define ERROR_CHECK(ret, num, msg)                                                                 \
    {                                                                                              \
        if (ret == num) {                                                                          \
            perror(msg);                                                                           \
            return -1;                                                                             \
        }                                                                                          \
    }
#define THREAD_ERROR_CHECK(ret, msg)                                                               \
    {                                                                                              \
        if (ret != 0) { fprintf(stderr, "%s:%s\n", msg, strerror(ret)); }                          \
    };

#endif // MYSELFC_H
