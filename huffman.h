#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataTypes.h"
#include "huffmanCode.h"

char* encode( char*, uint );
bool isIn( byte*, uint, byte );
uint countInList( byte*, uint, byte );	
ByteList* createByteList( byte*, uint );
bool isInElements( ByteListElement*, uint, byte );
uint countUnique( byte*, uint );
void sortByteList ( ByteList*, uint );
void swapBytes ( ByteList*, uint, uint );
void populateByteList ( ByteList*, byte*, uint );
ByteList* initializeByteList( byte*, uint );
Node* createHuffmanTree( ByteList* );
void printHuffmanTree( Node* );
uint findSmallestRoot( Node**, uint );
uint findSecondSmallestRoot( Node**, uint );
void addRoot( Node**, uint, Node*, Node* );
void removeRoot( Node**, uint, uint );
void combineRoots( Node**, uint, uint, uint );
Node* makeLeaf( ByteListElement* );
uint countRoots( Node**, uint );
