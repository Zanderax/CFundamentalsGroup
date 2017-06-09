#include "fileOperations.h"

void writeToFile( byte* data, uint dataSize, byte* fileName )
{
	FILE *fp;

	fp = fopen( fileName, "w" );

	uint i;

	for( i = 0; i < dataSize; ++i )
	{
		putc( data[i], fp );
	}

	fclose( fp );
}

uint getSizeOfFile( byte* fileName )
{
	FILE *fp;

	fp = fopen( fileName, "r");

	if( !fp )
		return 1;

	fseek( fp, 0L, SEEK_END );
	uint size = ftell( fp );
	fclose( fp );
	return size;
}

byte* readFromFile( uint* inputSize, byte* fileName )
{
}
