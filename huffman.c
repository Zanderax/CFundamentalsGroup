#include "huffman.h"

int main()
{
	/*byte data[dataSize] = 
	{ 
		'I', ' ', 'a', 'm', ' ', 'a', ' ', 'm', 'a', 's',
		't', 'e', 'r', ' ', 'a', 't', ' ', 't', 'y', 'p',
		'i', 'n', 'g', ' ', 'i', 'n', ' ', 'a', ' ', 'c',
		'h', 'a', 'r', ' ', 'a', 'r', 'r', 'a', 'y', 's'
	};*/
	
	byte data[arraySize] = 
	{ 
		'I', ' ', 'a', 'm', ' ', 'a', ' ', 'm', 'a', 's',
		't', 'e', 'r', ' ', 'a', 't', ' ', 't', 'y', 'p',
		'i', 'n', 'g', ' ', 'i', 'n', ' ',  'c',
		'h', 'a', 'r', ' ', 'a', 'r', 'r', 'a', 'y', 's'
	};

	byte *returnData = compress( data, arraySize );

	
	/*showOffEncoding( data, dataSize );*/

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

void showOffEncoding( byte *data, uint size )
{
	
	uint i;
	
	for( i = 0; i < size; ++i )
	{
		printf( "%c", data[i] );
	} 
	printf( "\n" );
	
	encode( data, size );

	for( i = 0; i < size; ++i )
	{
		printf( "%c", data[i] );
	} 
	printf( "\n" );

	decode( data, size );

	for( i = 0; i < size; ++i )
	{
		printf( "%c", data[i] );
	} 
	printf( "\n" );
}


byte* compress( byte *data, uint size ) 
{

	ByteList *byteList = createByteList( data, size );
	uint i;

	Node* node = createHuffmanTree( byteList );

	/*printHuffmanTree( node );*/

	Code* code = createHuffmanCode( node );

	byte* compressedData = calloc( size*5, sizeof( byte ) );

	int currentByte = 0, currentBit = 0;
	
	addHuffmanHeaderToByteArray( compressedData, code, data, &currentByte );
	
	addHuffmanDataToByteArray( compressedData, code, data, 
								&currentByte, &currentBit, size );

	printf("currentByte- %d\n", currentByte);

	printf("Digit   Binary   Char\n");
	for( i = 1; i < currentByte; i++)
	{
		printf("%5d - ", compressedData[i]);
		printDecToBin( compressedData[i] );
		printf(" - %c", compressedData[i]);
		printf( "\n");
	}



	/* TODO - Compress Data With Huffman Code */

	/* TODO - Return Huffman Code and Compressed Data */

	
	return data;
}

/*
Huffman Code Format
1 Byte - Number of Code Elements
FOR(Number of Code Elements)
{
	1 Byte - Data
	1 Byte - Path Length
	n Byte - Path
}
4 Byte - Number of Elements
x byte - Paths
*/

/*
	When it says n bytes then use the number stored above.
	e.g. 
		n Byte - Path
		n = Path Length

	x Bytes is untracked length, you keep reading for each number of elements
*/

void addHuffmanHeaderToByteArray(byte* compressedData, Code *code, byte* data, 
									int *currentByte )
{
	int byteOffSet = *currentByte;
	compressedData[byteOffSet++] = code->elementsCount;
	uint i;
	for( i = 0; i < code->elementsCount; ++i )
	{
		compressedData[byteOffSet++] = code->elements[i].data; 
		compressedData[byteOffSet++] = code->elements[i].pathLength;
		uint j;
		uint pathLength = (code->elements[i].pathLength / 8 );
		if ( (code->elements[i].pathLength % 8) )
		{
			++pathLength;
		}
		for( j = 0; j < pathLength; ++j)
		{
			compressedData[byteOffSet++] = code->elements[i].path[j]; 
		}
	}
	*currentByte = byteOffSet;
}


void addHuffmanDataToByteArray( byte *compressedData, Code *code, byte* data, 
								int *currentByte, int *currentBit, 
								uint dataSize )
{

	byte num = dataSize;
	printf("num = %d\n",num);
	putBitsInByteArray( &num, BYTE_SIZE, compressedData, currentByte, 
							currentBit );

	
	uint i; 
	for( i = 0; i < dataSize ; ++i )
	{
		CodeElement* codeElement = getCodeForByte( code, data[i] );
		uint j;
		
		putBitsInByteArray( codeElement->path, codeElement->pathLength, 
								compressedData, currentByte, currentBit );
	}

}

CodeElement* getCodeForByte( Code* code, byte data )
{
	uint i;
	for( i = 0; i < code->elementsCount; ++i )
	{
		if(code->elements[i].data == data )
		{
			return &(code->elements[i]);
		}
	}
}

void showOffCode( Code *code )
{
	/*printf( "BytesForPath = %u\n", code->bytesForPath );*/
	uint i, j;
	for( i = 0; i < code->elementsCount; ++i )
	{
		printf( "Node = %u\n", i );
		printf( "Data = %c\n", code->elements[i].data );
		printf( "PathLength = %u\n", code->elements[i].pathLength );
		printf( "Path = " );
		for( j = 0; j < code->bytesForPath; ++j )
		{
			printDecToBin( code->elements[i].path[j]);
			printf( " ");
		}
		printf( "\n" );
	}
}

void printDecToBin( byte  dec )
{
	int i;
	for( i = 0; i < 8; ++i )
	{
		printf("%d", getBit( dec, i ));
	}
}
