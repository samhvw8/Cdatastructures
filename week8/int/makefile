CC=gcc
CFLAGS=-c -Wall

SOURCES=interger.c dlink.c Queue.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=interger

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
	echo Clean done

