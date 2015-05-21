CC=gcc
CFLAGS=-c 

SOURCES=postfix.c linkstack.c Ginz.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=postfix

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC)  $(OBJECTS)  -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)	


