CFLAGS = -Wall -Wextra -Werror -std=c99
CC = gcc

gtin: main.c gtin.o
	$(CC) $(CFLAGS) -o gtin main.c gtin.o

gtin.o: gtin.c gtin.h gs1.h
	$(CC) $(CFLAGS) -c gtin.c

test: test.c gtin.c gtin.h gs1.h
	$(CC) $(CFLAGS)  -g -O0 -o test test.c gtin.c