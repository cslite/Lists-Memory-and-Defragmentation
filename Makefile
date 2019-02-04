CC=gcc
CFLAGS=-I.
DEPS = list.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

exe: list.o driver.o 
	$(CC) -o exe list.o driver.o 
