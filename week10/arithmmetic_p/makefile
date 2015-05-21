CC=gcc
CFLAGS= -g -c -Wall
LDFLAGS= -g
SOURCES=arith.c Btree.c linkstack.c Ginz.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=arith

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
