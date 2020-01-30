SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o)
CFLAGS = -Wall -g
DONTLINK = -c


main: $(SRCS)
	gcc $(CFLAGS) $^ -o $@

