CFLAGS = -Wall

all: myavl

myavl: avl.o
	cc main.c -o myavl


avl.o: avl.c avl.h
	cc avl.c -c $(CFLAGS)

clean:
	-rm -f *~ *.o *.out
purge: clean
	-rm -f myavl