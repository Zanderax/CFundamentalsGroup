CC=gcc
CFLAGS=-I.

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

huffman: huffman.o 
	gcc -o huffman huffman.o -I.
