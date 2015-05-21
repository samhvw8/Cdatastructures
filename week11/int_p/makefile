CC=gcc
CFLAGS= -c -Wall -Werror -Wextra 
LDFLAGS=
SRCS=int.c Btree.c BST.c
OBJS=$(SRCS:.c=.o)
EXECUTABLE=int


all: $(SRCS) $(EXECUTABLE)



debug: CFLAGS += -g
debug: LDFLAGS += -g
debug:  $(SRCS) $(EXECUTABLE)



profiling: CFLAGS += -pg
profiling: LDFLAGS += -pg
profiling: all

$(EXECUTABLE): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)


remake: clean all
redebug: clean debug
reprofiling: clean profiling
