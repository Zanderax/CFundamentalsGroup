#ifndef FILE_OPERATIONS
#define FILE_OPERATIONS

#include <stdio.h>

#include "dataTypes.h"

void writeToFile( byte* data, uint dataSize, byte* fileName );
byte* readFromFile( uint* inputSize, byte* fileName );
uint getSizeOfFile( byte* fileName );
#endif /* FILE_OPERATIONS */
