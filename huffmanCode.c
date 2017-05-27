#include "huffmanCode.h"

byte* createHuffmanCode( Node *node )
{
	byte *a = malloc( sizeof(byte) );
	*a='a';
	printf("%c/n", *a);
	setBit( a, 1, 1);
	printf("%c/n", *a);

	return a;
}

void setBit( byte *data, int bit, int value )
{
	if( bit < 0 || bit > 7 || ( value != 0 && value != 1 ) )
	{
		printf("GG");
		return;
	}

	*data ^= (-value ^ *data ) & ( 1 << bit );
}
