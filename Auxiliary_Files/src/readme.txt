// 动态库
clang -c -Ofast -ffast-math -flto -o epoll.o epoll.c
clang -shared -fPIC -Ofast -ffast-math -flto -o libepoll.dylib epoll.o

clang -dynamiclib epoll.c timerfd.c  -o libmydarwin.dylib -Ofast -fno-stack-protector -ffast-math -flto

// 静态库
clang -c -fPIC -Ofast -ffast-math -flto -o epoll.o epoll.c
ar -rcs libepoll.a epoll.o
mv libepoll.a ../lib/
