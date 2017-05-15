#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NAME_SIZE 50

typedef unsigned int uint;

typedef char byte;

typedef int bool;

#define TRUE 1
#define FALSE 0

#define dataSize 10

typedef struct {
	char name[MAX_NAME_SIZE];
	uint frontEndianCardNumber;
	uint backEndianCardNumber;
	int month;
	int year;
	int cvc;
} Card;

typedef struct {
	byte data;
	uint count;
} ByteListElement;

typedef struct {
	uint size;
	ByteListElement *elements;
} ByteList;

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

int main()
{
	byte data[dataSize] = { '1', '8', '1', '6', '1', '6', '8', '8', '7', '1' };
	byte *returnData = encode( data, dataSize );
	return 0;
}
/*
	encodes a stream of bytes into huffman
	in/out data - encoded into huffman
	in size - size of data
	out - byte - pointer to huffman code
*/

byte* encode( byte *data, uint size ) 
{
	byte unique[size];
	uint uniqueCount = 0;
	uint i;

	ByteList *byteList = createByteList( data, size );

	/* TODO - Create Huffman Tree */

	/* TODO - Create Huffman Code */

	/* TODO - Compress Data With Huffman Code */

	/* TODO - Return Huffman Code and Compressed Data */

	/* Display data */
	printf( "ByteList Size = %u\n", byteList->size );
	for (i = 0; i < byteList->size; ++i)
	{
		printf( "Data = %c\n", byteList->elements[i].data );
		printf( "Count = %d\n", byteList->elements[i].count );
	}
	
	return data;
}

ByteList* createByteList( byte* data, uint size)
{
	ByteList *byteList = initializeByteList( data, size );

	populateByteList( byteList, data, size );

	sortByteList( byteList, size );

	return byteList;
}

ByteList* initializeByteList( byte* data, uint size )
{
	/* Initalize ByteList */
	uint uniqueCount = countUnique( data, size );
	uint listSize = sizeof( ByteList ) + 
					sizeof( ByteListElement* ) * uniqueCount;
	ByteList * byteList = calloc( 1, listSize );

	/* Initalize Elements */
	byteList->elements = calloc( size, sizeof( ByteListElement ) );
	byteList->size = uniqueCount;
}

void populateByteList ( ByteList* byteList, byte* data, uint size )
{
	uint i, count = 0;
	for (i = 0; i < size; ++i)
	{
		if(!isInElements( byteList->elements, count, data[i] ))
		{
			byteList->elements[count].data = data[i];
			byteList->elements[count].count = 
					countInList( data, size, data[i] );
			++count;
		}		
	}
}

/* Selection Sort */
void sortByteList ( ByteList* list, uint size )
{
	uint i, j;
	uint maxCount, maxIndex;
	for (i = 0; i < size; ++i)
	{
		maxCount = 0;
		maxIndex = 0;
		
		for (j = i; j < size; ++j)
		{
			if (list->elements[j].count > maxCount)
			{
				maxCount = list->elements[j].count;
				maxIndex = j;
			}
		}
		swapBytes( list, i, maxIndex );
	}	
}

void swapBytes ( ByteList* list, uint first, uint second )
{
	ByteListElement temp = list->elements[first];
	list->elements[first] = list->elements[second];
	list->elements[second] = list->elements[first];
}

uint countUnique( byte* list, uint size )
{
	uint i, count = 0;
	byte unique[size];
	for (i = 0; i < size; ++i)
	{
		if ( !isIn( unique, count, list[i] ) )
		{
			unique[count] = list[i];
			count++;
		}
	}
	return count;
}



//Checks if byte is in a list
bool isIn( byte* list, uint size, byte value )
{
	uint i;
	for (i = 0; i < size; ++i)
		if (list[i] == value)
			return TRUE;

	return FALSE;
}

//Checks if byte is in a list of ByteListElements
bool isInElements( ByteListElement* list, uint size, byte value )
{
	uint i;
	for (i = 0; i < size; ++i)
		if (list[i].data == value)
			return TRUE;
	return FALSE;
}

//counts the number of unique elements in a byte list
uint countInList( byte* list, uint size, byte value )
{
	uint i, count = 0;
	for (i = 0; i < size; ++i)
		if (list[i] == value)
			++count;
	return count;
}
