CC=gcc
FLAGS = -Wall -Werror -Wextra -Warray-bounds -Wnonnull -lm
CFLAGS= -c $(FLAGS)
LDFLAGS= $(FLAGS)
SRCS=mergesort.c sort.c
OBJS=$(SRCS:.c=.o)
EXECUTABLE=mergesort
fileclean= gmon.out p.dat

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
	rm -rf *.o $(EXECUTABLE) $(fileclean)

remake: clean all
redebug: clean debug
reprofiling: clean profiling

