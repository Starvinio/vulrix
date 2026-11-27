CC = gcc
CLFLAGS = -Wall -Wextra -Iinclude

build/vulrix: build/main.o
	mkdir -p build
	$(CC) -o $@ $^ 

build/main.o: main.c
	mkdir -p build
	$(CC) $(CFLAGS) -o $@ -c $<
