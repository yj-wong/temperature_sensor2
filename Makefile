CC = gcc
CFLAGS = -lWarn -pedantic

tempread: tempread.o
	cc tempread.o -lm -o tempread

tempread.o: tempread.c
	$(CC) $(CFLAGS) -c -ansi $<
