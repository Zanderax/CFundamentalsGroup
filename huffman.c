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
	uint data;
	byte count;
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
Node createHuffmanTree( ByteList* );
void printHuffmanTree( Node* );
void printByteList( ByteList* );
uint findSmallestRoot( Node*, uint );
void addRoot( Node*, uint, Node*, Node* );
void removeRoot( Node*, uint, uint );

int main()
{
	byte data[dataSize] = { '1', '8', '1', '7', '1', '7', '8', '1', '7', '1' };
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
	uint i;
	for(i=0; i<byteList->size; ++i)
	{
		printf("Count = %u\n", byteList->elements[i].count);
		printf("Data = %c\n", byteList->elements[i].data);
	}

	Node node = createHuffmanTree( byteList );

	printHuffmanTree( &node );

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

	sortByteList( byteList, byteList->size );

	return byteList;
}

Node createHuffmanTree( ByteList* byteList )
{
	if (byteList == NULL || byteList->elements == NULL)
	{
		return;
	}

	// Set index to work in revserse so that we start with the smallest values

	uint byteListIndex = (byteList->size)-1;

	uint numberOfRoots = 0;

	// Make the inital node equal to the lowest frequency
	// Temp list of roots, we are only going to return one root.
	// Max number of roots = (total number of nodes)/2
	// The + 1 prevents errors when integer truncation occurs

	Node *roots = malloc( sizeof( Node ) * ( (byteList->size) / 2 + 1 ) );

	//Put the first root in with the two smallest leaves as 

	Node* first_leaf = malloc( sizeof( Node ) );
	first_leaf->count = byteList->elements[byteListIndex].count;
	first_leaf->data = byteList->elements[byteListIndex].data;
	--byteListIndex;

	Node* second_leaf = malloc( sizeof( Node ) );
	second_leaf->count = byteList->elements[byteListIndex].count;
	second_leaf->data = byteList->elements[byteListIndex].data;
	--byteListIndex;


	addRoot( roots, numberOfRoots, first_leaf, second_leaf );

	numberOfRoots++;
/*
	uint i;
	for (i = byteList->size - 3 ; i >= 0; ++i)
	{
		uint smallestRootIndex = findSmallestRoot( roots, numberOfRoots );

		uint sizeOfNextRoot = smallest + byteList->elements[i].count;
		uint sizeOfNextIndependantRoot = byteList->elements[i].count +				
										 byteList->elements[i-1].count;
		if( sizeOfNextRoot < sizeOfNextIndependantRoot )
		{
			
			TODO - Create new root as a parent of next and the current smallest root
			

		}
		else
		{
			TODO - Create new independant root from the next two elements
			 ++i; <- do this because you are using two elements
		}
	}	

	*/
	return roots[0];
}

void addRoot( Node* roots, uint index, Node* left, Node* right)
{
	roots[index].right = right;
	roots[index].left = left;
	roots[index].count = roots[index].left->count + roots[index].right->count; 
}

void removeRoot( Node* roots, uint size, uint index)
{
	uint i;
	for (i = index; i < size-1; ++i)
	{
		roots[i] = roots[i+1];
	}
}

uint findSmallestRoot( Node* roots, uint numberOfRoots )
{
	uint i, smallestIndex;
	for (i = 0; i < numberOfRoots; ++i)
	{
		if (roots[i].count > roots[smallestIndex].count)
		{
			smallestIndex = i;
		}
	}
	return smallestIndex;
}

void printHuffmanTree( Node *node )
{
	printf( "Node Count - %u\n", node->count );
	printf( "Node Data - %c\n", node->data );
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
	// Wouldn't cause a problem but saves CPU time.
	if (first==second)
		return;

	printf("Swap I1=%u V1=%c I2=%u V2=%c\n", first, list->elements[first].data, second, list->elements[second].data);
	ByteListElement temp = list->elements[first];
	list->elements[first] = list->elements[second];
	/*list->elements[second] = list->elements[first];*/
	list->elements[second] = temp;
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
