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
void showOffEncoding( byte*, uint );
void showOffCode( Code* );
void printDecToBin( int );

#endif /* HUFFMAN */
