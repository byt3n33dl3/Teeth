ssl.o: ssl.c ssl.h
	$(CC) $(CFLAGS) -c ssl.c -o $@

default: ssl.o
all: ssl.o