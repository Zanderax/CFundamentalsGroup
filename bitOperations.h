#ifndef BIT_OPERATIONS 
#define BIT_OPERATIONS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "dataTypes.h"

void setBit( byte*, int, int );
uint getBit( byte, int );
void putBitsInByteArray( byte* bytes, uint numberOfBits, byte* byteArray, 
							uint *byteOffSet, uint *bitOffSet );

#endif /* BIT_OPERATIONS */
