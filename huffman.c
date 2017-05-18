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
	char first_name[MAX_NAME_SIZE];
	char initial;
	char last_name[MAX_NAME_SIZE];
	long long unsigned int cardNumber;
	unsigned int month;
	unsigned int year;
	unsigned int cvc;
	unsigned int ID;
} Card;

typedef struct {
	byte data;
	uint count;
} ByteListElement;

typedef struct {
	uint size;
	ByteListElement *elements;
} ByteList;

typedef struct Node Node;

struct Node {
	byte value;
	Node *left;
	Node *right;
};

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
void printByteList( ByteList* );

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

/* TODO - Convert list of card structs to byte list */

/* TODO - Decompress */

byte* encode( byte *data, uint size ) 
{

	ByteList *byteList = createByteList( data, size );
	/*Node *node = createHuffmanTree( byteList );*/

	/*printHuffmanTree( node );*/

	/* TODO - Create Huffman Tree */

	/* TODO - Create Huffman Code */

	/* TODO - Compress Data With Huffman Code */

	/* TODO - Return Huffman Code and Compressed Data */

	
	return data;
}

ByteList* createByteList( byte* data, uint size)
{
	ByteList *byteList = initializeByteList( data, size );

	populateByteList( byteList, data, size );

	sortByteList( byteList, size );

	return byteList;
}

Node* createHuffmanTree( ByteList* byteList )
{
	if (byteList == NULL || byteList->elements == NULL)
	{
		return;
	}
	// Make the inital node equal to the lowest frequency
	// Temp list of roots, we are only going to return one root.
	// Max number of roots = (total number of nodes)/2
	// The + 1 prevents errors when integer truncation occurs
	// This is an area that could optomise for memeory is needed.

	Node *roots = malloc( sizeof( Node ) * ( (byteList->size) / 2 + 1 ) );

	int i;
	for (i = byteList->size - 1; i >= 0; ++i)
	{
		/*TODO - Find smallest root*/
		uint smallest = 0;
		uint sizeOfNextRoot = smallest + byteList->elements[i].count;
		uint sizeOfNextIndependantRoot = byteList->elements[i].count +				
										 byteList->elements[i-1].count;
		if( sizeOfNextRoot < sizeOfNextIndependantRoot )
		{
			/*TODO - Create new root as a parent of next and the current smallest root*/
		}
		else
		{
			/*TODO - Create new independant root from the next two elements*/
			/* ++i; <- do this because you are using two elements*/
		}
	}	

	Node* first_leaf = malloc( sizeof( Node ) );
	first_leaf->value = 'F';
	Node* second_leaf = malloc( sizeof( Node ) );
	
	return first_leaf;
}

void printHuffmanTree( Node *node )
{
	printf( "Node Value - %c\n", node->value );
	if( node->left != NULL)
	{
		printf("Left\n");
		printHuffmanTree( node->left );
	}
	if( node->right != NULL)
	{
		printf("Right\n");
		printHuffmanTree( node->right );
	}
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

void printByteList( ByteList *byteList )
{
	uint i;
	/* Display data */
	printf( "ByteList Size = %u\n", byteList->size );
	for (i = 0; i < byteList->size; ++i)
	{
		printf( "Data = %c\n", byteList->elements[i].data );
		printf( "Count = %d\n", byteList->elements[i].count );
	}
}
