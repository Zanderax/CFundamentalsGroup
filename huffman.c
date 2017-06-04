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

	byte *returnData = compress( data, dataSize );

	
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
	
	for( i = 0; i < dataSize; ++i )
	{
		printf( "%c", data[i] );
	} 
	printf( "\n" );
	
	encode( data, dataSize );

	for( i = 0; i < dataSize; ++i )
	{
		printf( "%c", data[i] );
	} 
	printf( "\n" );

	decode( data, dataSize );

	for( i = 0; i < dataSize; ++i )
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

	/*printHuffmanTree( node ); */

	Code* code = createHuffmanCode( node );

	showOffCode( code );

	/* TODO - Compress Data With Huffman Code */

	/* TODO - Return Huffman Code and Compressed Data */

	
	return data;
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

void printDecToBin( int dec )
{
	int bin = 128;
	while(bin)
	{
		if((dec - bin) >= 0)
		{
			dec -= bin;
			printf("1");
		}
		else
		{
			printf("0");
		}
		bin /= 2;
	}
}
