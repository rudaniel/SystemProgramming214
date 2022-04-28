CC = gcc
CFLAGS = -std=c99 -Wall -g -pthread

ww: ww.c wordwrap.c 
	$(CC) $(CFLAGS) $^ -o $@
test: test.c wordwrap.c
	$(CC) $(CFLAGS) $^ -o $@