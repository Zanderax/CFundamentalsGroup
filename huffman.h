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

byte* compress( byte*, uint );
CodeElement* getCodeForByte( Code*, byte ); 
void showOffEncoding( byte*, uint );
void showOffCode( Code* );
void printDecToBin( int );
void addHuffmanHeaderToByteArray(byte* compressedData, Code *code, byte* data, 
									uint *currentByte );
void addHuffmanDataToByteArray( byte* compressedData, Code *code, byte* data, 
									uint *currentByte, uint *currentBit,
									uint dataSize );

#endif /* HUFFMAN */
