#include "keygen.h"

int main( void )
{
	generateKey();
	return 0;
}

void generateKey( void )
{
	/* 
		This should use <time.h> to generate a random key but I can't import   
		Thanks Obama.
	*/
	FILE *fp = fopen( "../xor.key", "w" );
	if ( fp == NULL )
	{
		printf( "Error creating key file." );
		return;
	}
	char key = 'a';
	fwrite( &key, sizeof( char ), 1, fp );
	fclose( fp );
}
