CC=gcc
CFLAGS=-I. -g

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

huffman: huffman.o 
	gcc -o huffman.out huffman.o -I.
