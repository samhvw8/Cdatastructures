CC=gcc
FLAGS = -Wall -Werror -Wextra -Warray-bounds -Wnonnull -lm
CFLAGS= -c $(FLAGS)
LDFLAGS= $(FLAGS)
SRCS=testsort.c sort.c
OBJS=$(SRCS:.c=.o)
EXECUTABLE=testsort


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
