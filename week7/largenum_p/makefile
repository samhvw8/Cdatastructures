CC=gcc
CFLAGS=-c -Wall

SOURCES=largenum.c linkstack.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=largenum

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS)  -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)


