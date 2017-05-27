#ifndef HUFFMAN_CODE
#define HUFFMAN_CODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataTypes.h"

byte* createHuffmanCode( Node* ); 
void setBit( byte*, int, int );
uint findTreeDepth( Node* );
uint countLeafs( Node* );

#endif /* HUFFMAN_CODE*/
