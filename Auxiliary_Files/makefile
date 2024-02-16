SRCS:=$(wildcard *.c)
OBJC:=$(patsubst %.c, %, $(SRCS))
all:$(OBJC)
%: %.c
	gcc -Wall -g0 -lpthread $^ -o $@

.PHONY:cleanup rebuild
cleanup:
	$(RM) $(OBJC)
rebuild: cleanup all
