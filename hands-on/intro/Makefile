SOURCES     =      $(wildcard *.c)
EXES        =      $(SOURCES:.c=.x)

CC          =      oshcc
CFLAGS      =      -O3 -g

CXX         =      oshCC
CXXFLAGS    =      $(CFLAGS)



.PHONY:		all	clean

.SUFFIXES:	.x

all:	$(EXES)

pairwise-toobig.x:	pairwise-toobig.c	array-utils.h
	$(CC) $(CFLAGS) -o $@ $<

pairwise-only.x:	pairwise-only.c		array-utils.h
	$(CC) $(CFLAGS) -o $@ $<


%.x:	%.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o
	rm -f *.x
