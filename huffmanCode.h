#ifndef HUFFMAN_CODE
#define HUFFMAN_CODE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataTypes.h"

Code* createHuffmanCode( Node* ); 
void populateHuffmanCode( Code*, Node* );
void setBit( byte*, int, int );
uint findTreeDepth( Node* );
uint countLeafs( Node* );
void getLeafNodes( Node*, Node**, uint );

#endif /* HUFFMAN_CODE*/
