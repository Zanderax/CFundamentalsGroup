#include "bitOperations.h"

void setBit( byte *data, int bit, int value )
{
	/* Swap the endianess of the bit so it writes from left to right */
	/*bit = -(bit - 7);*/
	if( bit < 0 || bit > 7 || ( value != 0 && value != 1 ) )
	{
		return;
	}
	*data ^= (-value ^ *data ) & ( 1 << bit );
}

uint getBit( byte data, int bit )
{
	return ( data >> bit ) & 1;
}

void putBitsInByteArray( byte* bytes, uint numberOfBits, byte* byteArray, 
							uint *byteOffSet, uint *bitOffSet )
{
	uint i;
	for( i = 0; i < numberOfBits; ++i )
	{
		int bitValue = getBit( bytes[*byteOffSet], i );
		setBit( &(byteArray[*byteOffSet]), *bitOffSet, bitValue );
		
		(*bitOffSet)++;
		
		if( *bitOffSet % 8 )
		{
			(*byteOffSet)++;
			(*bitOffSet) = 0;
			
		}
	}
}

