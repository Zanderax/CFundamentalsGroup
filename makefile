CC=gcc
CFLAGS=-I. -g

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

huffman: huffman.o 
	gcc -o huffman huffman.o -I.
