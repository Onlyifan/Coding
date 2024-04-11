// 动态库
clang -c -Ofast -ffast-math -flto -o epoll.o epoll.c
clang -shared -fPIC -Ofast -ffast-math -flto -o libepoll.dylib epoll.o

clang -g -dynamiclib epoll.o  -o libepoll.dylib

// 静态库
clang -c -fPIC -Ofast -ffast-math -flto -o epoll.o epoll.c
ar -rcs libepoll.a epoll.o
