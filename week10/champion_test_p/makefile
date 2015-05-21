CC=gcc
CFLAGS= -g -c -Wall
LDFLAGS= -g
SOURCES=champion.c Btree.c Queue.c dlink.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=champion

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
