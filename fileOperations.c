#include "fileOperations.h"

int writeToFile( byte* data, uint dataSize, byte* fileName )
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
