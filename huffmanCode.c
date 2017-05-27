#include "huffmanCode.h"

byte* createHuffmanCode( Node *node )
{
	/* Find how long the code will be so we can allocate enough memory. 	  */
	/* Memory needed is 1 byte for the ascii and x bytes for the code 		  */
	/* Where x is equal to the ceiling function of maxDepth / 8				  */
	uint maxDepth = findTreeDepth( node );

	uint leafs = countLeafs( node );

	uint maxCodeLength = maxDepth / 8;

	if( maxDepth % 8 != 0)
	{
		maxCodeLength++;
	}

	/* Memory for each leaf, 1 byte each for ascii and x bytes for code		  */
	int memorySize = ( sizeof( byte ) * ( 1 + maxCodeLength ) ) * ( leafs );

	byte *code = malloc( memorySize );

	return code;
}

void setBit( byte *data, int bit, int value )
{
	if( bit < 0 || bit > 7 || ( value != 0 && value != 1 ) )
	{
		return;
	}

	*data ^= (-value ^ *data ) & ( 1 << bit );
}

uint findTreeDepth( Node *node )
{
	uint maxDepth = 0, rightDepth = 0;

	/* If no child nodes then return 0 */
	if( node->left == NULL || node->right == NULL)
	{
		return maxDepth;
	}
 
	maxDepth++;
	
	if( node->left != NULL ) 
	{
		maxDepth = findTreeDepth( node->left );
	}

	if(node->right != NULL )
	{
		rightDepth = findTreeDepth( node->right );
		if( rightDepth > maxDepth )
		{
			maxDepth = rightDepth;
		}
	}

	/* Add the depth for this level and return */
	return ++maxDepth;
}

uint countLeafs( Node *node )
{
	uint leafs = 0;

	if ( node->left == NULL && node->right == NULL )
	{
		return 1;
	}

	if( node->left != NULL ) 
	{
		leafs += countLeafs( node->left );
	}

	if( node->right != NULL ) 
	{
		leafs += countLeafs( node->right );
	}

	return leafs;
}
