@SET_MAKE@
CC = @CC@
CXX = @CXX@
AS = @CC@
LD = @CC@
CPP = @CC@
CFLAGS = @CFLAGS@ @CFLAGS_EXTRA@ @SSL-ATTACK_CFLAGS@
ASFLAGS = @ASFLAGS@ -c @EXTRA_AS_FLAGS@
LDFLAGS = @LDFLAGS@ @SSL-ATTACK_LIBS@

ssl.o: ssl.c ss.h
	$(CC) $(CFLAGS) -c ssl.c -o $@

default: ssl.o
all: ssl.o

clean:

distclean: clean
	$(RM) Makefile