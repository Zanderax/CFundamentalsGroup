#include "huffman.h"

int main()
{
	byte data[dataSize] = 
	{ 
		'I', ' ', 'a', 'm', ' ', 'a', ' ', 'm', 'a', 's',
		't', 'e', 'r', ' ', 'a', 't', ' ', 't', 'y', 'p',
		'i', 'n', 'g', ' ', 'i', 'n', ' ', 'a', ' ', 'c',
		'h', 'a', 'r', ' ', 'a', 'r', 'r', 'a', 'y', 's'
	};
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

	Node* node = createHuffmanTree( byteList );

	printHuffmanTree( node );

	byte* code = createHuffmanCode( node );

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

Node* createHuffmanTree( ByteList* byteList )
{
	if (byteList == NULL || byteList->elements == NULL)
	{
		return;
	}

	Node **roots = malloc( sizeof( Node* ) *  (byteList->size)  );

	uint i;
	for( i = 0; i < byteList->size; ++i )
	{
		
		roots[i] = makeLeaf( &byteList->elements[i] );
	}

	uint numberOfRoots = countRoots( roots, byteList->size );
	while (numberOfRoots > 1)
	{
		uint smallest = findSmallestRoot( roots, numberOfRoots );
		uint secondSmallest = findSecondSmallestRoot( roots, numberOfRoots );
		combineRoots( roots, byteList->size, smallest, secondSmallest );
		numberOfRoots--;
	}
	
	return roots[0];
}

uint countRoots( Node** roots, uint size )
{
	uint count = 0;
	while( count < size && roots[count++] != NULL );
	return count;
}

Node* makeLeaf( ByteListElement* element )
{
	Node *leaf = malloc( sizeof( Node ) );
	leaf->count = element->count;
	leaf->data = element->data;
	return leaf;
}

void addRoot( Node** roots, uint index, Node* left, Node* right )
{
	Node *newRoot = malloc( sizeof( Node ) );
	newRoot->right = right;
	newRoot->left = left;
	newRoot->count = left->count + right->count;
	roots[index] = newRoot;
}

void removeRoot( Node** roots, uint size, uint index)
{
	roots[index] = NULL;
	uint i;
	for (i = index; i < size-1; ++i)
	{
		roots[i] = roots[i+1];
	}
}

void combineRoots( Node** roots, uint size, uint firstIndex, uint secondIndex )
{
	if (firstIndex < secondIndex)
	{
		addRoot( roots, firstIndex, roots[firstIndex], roots[secondIndex] );
		removeRoot( roots, size, secondIndex );
	}
	else
	{
		addRoot( roots, secondIndex, roots[secondIndex], roots[firstIndex] );
		removeRoot( roots, size, firstIndex );
	}
}

uint findSmallestRoot( Node** roots, uint numberOfRoots )
{
	uint i, smallestIndex = 0;
	for (i = 1; i < numberOfRoots; ++i)
	{
		if (roots[i]->count < roots[smallestIndex]->count)
		{
			smallestIndex = i;
		}
	}
	return smallestIndex;
}

uint findSecondSmallestRoot( Node** roots, uint numberOfRoots )
{
	if(numberOfRoots < 2)
		return;

	uint i, smallestIndex = 0, secondSmallestIndex = 1;
	if( roots[smallestIndex] > roots[secondSmallestIndex])
	{
		smallestIndex = 1;
		secondSmallestIndex = 0;
	}

	for (i = 2; i < numberOfRoots; ++i)
	{
		if (roots[i]->count < roots[smallestIndex]->count)
		{
			secondSmallestIndex = smallestIndex;
			smallestIndex = i;
		}
		else if (roots[i]->count < roots[secondSmallestIndex]->count)
		{
			secondSmallestIndex = i;
		}
	}
	return secondSmallestIndex;
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

	ByteListElement temp = list->elements[first];
	list->elements[first] = list->elements[second];
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


