CC=gcc
CFLAGS= -c -Wall -Werror -Wextra
LDFLAGS=
SRCS=dict.c Btree.c BST.c Ginz.c
OBJECTS=$(SRCS:.c=.o)
EXECUTABLE=dict

all: $(SRCS) $(EXECUTABLE)


debug: CFLAGS += -g
debug: LDFLAGS += -g
debug:  $(SRCS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
remake: clean all
redebug: clean debug
