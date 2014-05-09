
CC=g++

CFLAGS=-c -Wall 
PKGS = `pkg-config opencv --libs --cflags`

all: bound_rec

bound_rec:  bound_rec.o main.o 
	$(CC) $(PKGS) main.o bound_rec.o -o boundary

bound_rec.o: bound_rec.cpp
	$(CC) $(CFLAGS) bound_rec.cpp $(PKGS)

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp $(PKGS)

clean:
	rm -rf *o bound_rec
