CC = g++
CFLAGS = -O3 -Wall -Wextra -Werror -fstack-protector-strong -Wshadow -Wformat=2 -Wconversion

all: main

main: main.o board.o lidi.o utils.o simulation.o Makefile
	$(CC) $(CFLAGS) -o main main.o board.o lidi.o utils.o simulation.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

simulation.o: simulation.cpp simulation.h
	$(CC) $(CFLAGS) -c simulation.cpp

board.o: board.cpp board.h
	$(CC) $(CFLAGS) -c board.cpp

lidi.o: lidi.cpp lidi.h
	$(CC) $(CFLAGS) -c lidi.cpp
	
utils.o: utils.cpp utils.h
	$(CC) $(CFLAGS) -c utils.cpp

valgrind: main
	time valgrind --show-leak-kinds=all --track-origins=yes ./main

clean:
	rm -f main *.o
	
run: main
	time ./main