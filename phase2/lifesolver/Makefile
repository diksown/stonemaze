CC = g++
CFLAGS = -g -O3 -march=native -Wall -Wextra -Wpedantic -Werror -fstack-protector-strong

all: main

main: main.o board.o
	$(CC) $(CFLAGS) -o main main.o board.o lidi.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

board.o: board.cpp board.h
	$(CC) $(CFLAGS) -c board.cpp

lidi.o: lidi.cpp lidi.h
	$(CC) $(CFLAGS) -c lidi.cpp

valgrind: main
	time valgrind --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -f main *.o
	
run: main
	time ./main