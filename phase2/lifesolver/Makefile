CC = g++
CFLAGS = -g -O3 -march=native -Wall -Wextra -Wpedantic -Werror -fstack-protector-strong -fstack-protector-strong -Werror

all: main

main: main.cpp
	$(CC) $(CFLAGS) -o main main.cpp

valgrind: main
	valgrind --show-leak-kinds=all ./main


clean:
	rm -f main