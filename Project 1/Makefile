CC = gcc
CFLAGS = -std=c99 -Wall -g 

test: testCases.c mymalloc.c 
	$(CC) $(CFLAGS) $^ -o $@
memgrind: memgrind.c mymalloc.c 
	$(CC) $(CFLAGS) $^ -o $@
