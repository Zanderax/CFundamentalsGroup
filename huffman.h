#ifndef HUFFMAN
#define HUFFMAN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataTypes.h"
#include "bytelist.h"
#include "huffmanTree.h"
#include "huffmanCode.h"

byte* compress( byte*, uint, uint* );
CodeElement* getCodeForByte( Code*, byte ); 
void showOffEncoding( byte*, uint );
void showOffCode( Code* );
void printDecToBin( byte );
void addHuffmanHeaderToByteArray(byte* compressedData, Code *code, byte* data, 
									int *currentByte );
void addHuffmanDataToByteArray( byte* compressedData, Code *code, byte* data, 
									int *currentByte, int *currentBit,
									uint dataSize );

#endif /* HUFFMAN */
