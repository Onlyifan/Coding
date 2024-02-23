#ifndef MYSELFC_H
#define MYSELFC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <ctype.h>
#include <time.h>
#include <syslog.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <dirent.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <sys/stat.h>

#ifdef __linux__
#include <sys/sendfile.h>
#endif // __linux__


#define ARR_LEN(arr) (sizeof(arr) / sizeof(arr[0]))
#define ARGS_CHECK(argc,num) {if(argc!=num){fprintf(stderr,"args error!\n");return -1;}}
#define ERROR_CHECK(ret,num,msg) {if(ret==num){perror(msg); return -1;}}
#define THREAD_ERROR_CHECK(ret,msg) {if(ret!=0){fprintf(stderr,"%s:%s\n",msg,strerror(ret));}};

#endif // MYSELFC_H
