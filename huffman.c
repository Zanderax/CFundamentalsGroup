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

