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
	code->bytesForPath = maxCodeLength+1;
	code->elements = malloc( sizeof( CodeElement ) );
	uint i;
	for( i = 0; i < code->elementsCount; ++i )
	{
	}

	populateHuffmanCode( code, node );

	return code;
}

void populateHuffmanCode( Code* code, Node* node )
{
	byte* path = malloc( sizeof( byte ) * ( code->bytesForPath ) );
	printf("Code path 00-%u\n", path[0] );
	path[0] = 100;
	printf("Code path 00-%u\n", path[0] );
	printf("Code path 11-%u\n", path[1] );
	path[1] = 101;
	printf("Code path 11-%u\n", path[1] );
	uint i;
	for( i = 0; i < code->bytesForPath; ++i)
	{
		path[i] = 0;
	}
	uint currentNode = 0;
	nodeToCode( code, node, 0, path, &currentNode );
	printf("code bytesForPath = %u\n", code->bytesForPath);
}

void nodeToCode( Code* code, Node* node, 
				 uint currentDepth, byte* path, uint* currentNode )
{
	uint currentPathOffset = *currentNode * code->bytesForPath;
	printf("Code node-%u\n", *currentNode );
	printf("Code bytesForPath-%u\n", code->bytesForPath );
	printf("Code currentPathOffset-%u\n", currentPathOffset );
	printf("Code path-%u\n", *path );
	if ( node->left == NULL && node->right == NULL )
	{
		printf("Set = %c\n", node->data);
		printf("aCode path-%u\n", *path );
		setCode( code, node, path, *currentNode, currentDepth );
		printf("bCode path-%u\n", *path );

		(*currentNode)++;
		return;
	}

	if( node->left != NULL ) 
	{
		printf("Set bit left - off=%u  depth=%u\n", currentPathOffset, currentDepth);
		setBit( &path[currentPathOffset], currentDepth % 8 , 0);
		nodeToCode( code, node->left, currentDepth + 1, path, currentNode );
	}

	if( node->right != NULL )
 	{
		printf("Set bit right - off=%u  depth=%u\n", currentPathOffset, currentDepth);
		setBit( &path[currentPathOffset], currentDepth % 8 , 1);
		nodeToCode( code, node->right, currentDepth + 1, path, currentNode );
		setBit( &path[currentPathOffset], currentDepth % 8 , 0);
	}
}

void setCode( Code* code, Node* node, byte* path, uint currentNode, uint depth )
{
	printf("1Code path-%u\n", *path );
	uint currentPathOffset = currentNode * code->bytesForPath;
	printf("2Code path-%u\n", *path );
	code->elements[currentNode].data = node->data;
	printf("3Code path-%u\n", *path );
	uint i;
	printf("4Code path-%u\n", *path );
	printf("Element path = %p\n", code->elements[currentNode].path);
	printf("Path = %p\n", path); 
	code->elements[currentNode].path = malloc( sizeof( byte ) * code->bytesForPath );
	printf("Element path = %p\n", &(code->elements[currentNode].path[0]));
	printf("Path = %p\n", path); 
	printf("5Code path-%u\n", *path );
	for( i = 0; i < code->bytesForPath; ++i )
	{
		printf("6Code path-%u\n", path[i] );
		/**(code->elements[currentNode].path[currentPathOffset + i]) = path[i];*/
		printf("7Code path-%u\n", path[i] );
	}
}

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
