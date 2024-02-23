SRCS:=$(wildcard *.c)
EXES:=$(patsubst %.c,%,$(SRCS))
CC:=gcc
CFLAGS := -g0
LIDFLAGS := -lepoll -lpthread

all: $(EXES)

%: %.c
	$(CC) $^ $(CFLAGS) $(LIDFLAGS) -o $@

clean:
	$(RM) $(EXES)

rebuild: clean all
