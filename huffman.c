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

#define dataSize 5

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
	int count;
} ByteListElement;

typedef struct {
	int size;
	ByteListElement element[];
} ByteList;

char* encode( char*, uint );
bool isIn( byte*, uint, byte );
uint countInList( byte*, uint, byte );	
ByteList* countBytes( byte* list, uint size)
uint countUnique( byte*, uint );

int main()
{
	printf( "Huffman::Main()\n");
	byte data[dataSize] = { 1, 2, 3, 2, 1 };
	byte *returnData = encode( data, dataSize );
	return 0;
}
/*
	encodes a stream of bytes into huffman
	in/out data - encoded into huffman
	in size - size of data
	out - byte - pointer to huffman code
*/

//TEMP - Currently puts all unique values into unique[] and prints them all
byte* encode( byte *data, uint size ) 
{
	byte unique[size];
	uint uniqueCount = 0;
	uint i;
	
	for (i = 0; i < size; ++i)
	{
		if (!isIn( unique, size, data[i] ))
		{
			unique[uniqueCount] = data[i];
			++uniqueCount;	
		}
	}

	for (i = 0; i < uniqueCount; ++i)
		printf( "%d\n", unique[i] );

	return data;
}

ByteList* countBytes( byte* list, uint size)
{
	/* Initalize ByteList to correct length */
	uint unique = countUnique( list, size );
	uint listSize = sizeof( ByteList ) + sizeof( ByteListElement ) * unique;
	ByteList * byteList = calloc( listSize , 1 );
	byteList->size = unique;

	uint i;
	for (i = 0; i < size; ++i)
	{
		i++;
	}

	return byteList;
}

uint countUnique( byte* list, uint size )
{
	uint i, count;
	byte unique[size];
	for (i = 0; i < size; ++i)
	{
		if ( !isIn( unique, count, list[i] ) )
		{
			unique[count] = list[i];
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

//counts the number of unique elements in a byte list
uint countInList( byte* list, uint size, byte value )
{
	uint i, count = 0;
	for (i = 0; i < size; ++i)
		if (list[i] == value)
			++count;
	return count;
}
