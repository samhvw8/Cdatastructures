CC=gcc
CFLAGS=-c -Wall

SOURCES=undo.c Ginz.c linkstack.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=undo

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)	
	echo Clean done

