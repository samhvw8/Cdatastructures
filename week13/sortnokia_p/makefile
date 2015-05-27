CC=gcc
FLAGS = -Wall -Werror -Wextra -Warray-bounds -Wnonnull -lm
CFLAGS= -c $(FLAGS)
LDFLAGS= $(FLAGS)
SRCS=sortnokia.c sort.c
OBJS=$(SRCS:.c=.o)
EXECUTABLE=sortnokia
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

