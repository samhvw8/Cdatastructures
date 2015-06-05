CC=gcc
CFLAGS=-g -c -Wall
LDFLAGS= -g
SOURCES=computers.c dlink.c Queue.c Ginz.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=computers

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
