CC=gcc
CFLAGS=-Wall -g -I.
LIBS=-pthread -lpigpio -lrt
DEPS=

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

TARGET=main

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	sudo ./$(TARGET)