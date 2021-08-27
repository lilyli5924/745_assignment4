INCLUDE = /usr/local/include
LIB = /usr/local/lib
CC = gcc
CFLAGS = -I$(INCLUDE) -L$(LIB) -c -O3
LDFLAGS = -Wall -lm  -lc
SOURCES = full_scan.c fault.c main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = fault_sim_atpg

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS) $(EXECUTABLE) *~
