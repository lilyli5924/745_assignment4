INCLUDE = /usr/local/include
LIB = /usr/local/lib
CC = g++
CFLAGS = -I$(INCLUDE) -L$(LIB) -c -O3
LDFLAGS = -Wall -lm  -lc
SOURCES = timeout.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = run_timeout

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE) *~
