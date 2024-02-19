SRCS:=$(wildcard *.c)
OBJC:=$(patsubst %.c, %, $(SRCS))
all:$(OBJC)
%: %.c
	gcc -Wall -g0 -lpthread $^ -o $@

.PHONY:clean rebuild
clear:
	$(RM) $(OBJC)
rebuild: clear all
