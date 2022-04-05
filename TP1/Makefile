CC=gcc
CFLAGS=-Wall -Werror

all: test_pile test_abr test_file test_avl

test_abr: test_abr.o pile.o file.o abr.o
	$(CC) -o $@ $^ -lm

test_avl: test_avl.o pile.o file.o avl.o abr.o
	$(CC) -o $@ $^ -lm

test_file : test_file.o file.o
	$(CC) -o $@ $^

test_pile : test_pile.o pile.o
	$(CC) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c $<


abr.o: abr.c pile.h file.h
avl.o: avl.c pile.h file.h
pile.o: pile.h pile.c abr.h
file.o: file.h file.c
test_abr.o: test_abr.c abr.h
test_avl.o: test_avl.c avl.h
test_pile.o: test_pile.c abr.h pile.h
test_file.o: test_file.c abr.h file.h

clean:
	rm -f *.o *~ test_abr test_pile test_file test_avl


