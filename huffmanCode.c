#include "huffmanCode.h"

Code* createHuffmanCode( Node *node )
{
	/* Find how long the code will be so we can allocate enough memory. 	  */
	/* Memory needed is 1 byte for the ascii and x bytes for the code 		  */
	/* Where x is equal to the ceiling function of maxDepth / 8				  */
	uint maxDepth = findTreeDepth( node );

	uint maxCodeLength = maxDepth / 8;

	if( maxDepth % 8 != 0)
	{
		maxCodeLength++;
	}

	Code *code = malloc( sizeof( Code ) );
	code->elementsCount = countLeafs( node );
	code->bytesForPath = maxCodeLength + 1;
	code->elements = malloc( sizeof( CodeElement ) );
	uint i;
	for( i = 0; i < code->elementsCount; ++i )
	{
		code->elements[i].path = malloc( sizeof( byte ) * code->bytesForPath );
	}

	populateHuffmanCode( code, node );

	return code;
}

void populateHuffmanCode( Code* code, Node* node )
{
	byte* path = malloc( sizeof( byte ) * ( code->bytesForPath ) );
	uint currentNode = 0;
	nodeToCode( code, node, 0, path, &currentNode );
}

void nodeToCode( Code* code, Node* node, 
				 uint currentDepth, byte* path, uint* currentNode )
{
	if ( node->left == NULL && node->right == NULL )
	{
		setCode( code, node, path, *currentNode );
		*currentNode++;
		return;
	}

	uint currentPathSize = currentDepth / 8;

	if( node->left != NULL ) 
	{
		setBit( &path[currentPathSize], currentDepth % 8 , 0);
		nodeToCode( code, node->left, currentDepth + 1, path, currentNode );
	}

	if( node->right != NULL ) 
	{
		setBit( &path[currentPathSize], currentDepth % 8 , 1);
		nodeToCode( code, node->right, currentDepth + 1, path, currentNode );
	}
}

void setCode( Code* code, Node* node, byte* path, uint currentNode )
{
	code->elements[currentNode].data = node->data;
	uint i;
	for( i = 0; i < code->bytesForPath; ++i )
	{
		code->elements[currentNode].path = path;
	}
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
