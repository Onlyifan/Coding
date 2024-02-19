SRCS:=$(wildcard *.c)
OBJS:=$(patsubst %.c,%.o,$(SRCS))
CC:=clang
server:$(OBJS)
	$(CC) $^ -o $@
%.o:%.c
	$(CC) -c $^ -o $@ -g -DLOG_DEBUG
clean:
	$(RM) $(OBJS) server
rebuild:clean all
