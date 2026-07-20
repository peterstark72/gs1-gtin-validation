CFLAGS = -Wall -Wextra -Werror -std=c99
CC = gcc

gtin: main.c gtin.o gcp.o
	$(CC) $(CFLAGS) -o gtin main.c gtin.o gcp.o

gtin.o: gtin.c gtin.h gcp.h
	$(CC) $(CFLAGS) -c gtin.c

gcp.o: gcp.c gtin.h gcp.h
	$(CC) $(CFLAGS) -c gcp.c

test: test.c gtin.c gcp.c gtin.h gcp.h
	$(CC) $(CFLAGS)  -g -O0 -o test test.c gtin.c gcp.c

clean:
	rm -f gtin test *.o