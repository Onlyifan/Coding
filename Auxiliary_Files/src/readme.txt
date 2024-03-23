clang -c -Ofast -ffast-math -flto -o epoll.o epoll.c
clang -shared -fPIC -Ofast -ffast-math -flto -o libepoll.dylib epoll.o
