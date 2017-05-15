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

#define dataSize 9

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
ByteList* countBytes( byte*, uint );
bool isInElements( ByteListElement*, uint, byte );
uint countUnique( byte*, uint );

int main()
{
	byte data[dataSize] = { '1', '1', '1', '1', '1', '6', '8', '8', '7' };
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

	ByteList *byteList = countBytes( data, size );
/* TODO - Data is not being put in the array. Run and see. */	
	printf( "ByteList Size = %u\n", byteList->size );
	for (i = 0; i < byteList->size; ++i)
	{
		printf( "Data = %c\n", byteList->elements[i].data );
		printf( "Count = %d\n", byteList->elements[i].count );
	}
	
	return data;
}

ByteList* countBytes( byte* list, uint size)
{
	/* Initalize ByteList to correct length */
	uint uniqueCount = countUnique( list, size );
	uint listSize = sizeof( ByteList ) + 
					sizeof( ByteListElement* ) * uniqueCount;
	ByteList * byteList = calloc( 1, listSize );

	byteList->elements = calloc( size, sizeof( ByteListElement ) );
	printf( "UniqueCount = %u\n", uniqueCount );	
	byteList->size = uniqueCount;

	uint i, count = 0;
	for (i = 0; i < size; ++i)
	{
		if(!isInElements( byteList->elements, count, list[i] ))
		{
			byteList->elements[count].data = list[i];
			byteList->elements[count].count = 
					countInList( list, size, list[i] );
			++count;
		}		
	}

	return byteList;
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
