CC=gcc
FLAGS = -Wall -Werror -Wextra -Warray-bounds -Wnonnull
CFLAGS= -c $(FLAGS)
LDFLAGS= $(FLAGS)
SRCS=poly.c dlink.c Ginz.c
OBJS=$(SRCS:.c=.o)
EXECUTABLE=poly
another= gmon.out

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
	rm -rf *.o $(EXECUTABLE) $(another)

remake: clean all
redebug: clean debug
reprofiling: clean profiling

