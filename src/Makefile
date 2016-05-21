CC=gcc
CFLAGS= -Wall -I.
DEPS = virtualCube.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: virtualCube.o
