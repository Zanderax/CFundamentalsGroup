#ifndef DATA_TYPES
#define DATA_TYPES

typedef char byte;
#define MAX_NAME_SIZE 50

typedef unsigned int uint;

typedef int bool;

#define TRUE 1
#define FALSE 0


#define arraySize 40 
#define BYTE_SIZE 8

/* 
	The theroetical maximum size for the headers is 66048 bytes.
	The full calculation and justification can be found in the report.
*/
#define MAX_HEADER_SIZE 66048 

typedef struct 
{
	char first_name[MAX_NAME_SIZE];
	char initial;
	char last_name[MAX_NAME_SIZE];
	long long unsigned int cardNumber;
	unsigned int month;
	unsigned int year;
	unsigned int cvc;
	unsigned int ID;
} Card;

typedef struct Node Node;

struct Node 
{
	byte data;
	uint count;
	Node *left;
	Node *right;
};

typedef struct CodeElement
{
	byte data;
	byte* path;
	uint pathLength;
} CodeElement;

typedef struct Code
{
	unsigned char elementsCount;
	uint bytesForPath;
	CodeElement *elements;
} Code;


typedef struct 
{
	byte data;
	uint count;
} ByteListElement;

typedef struct 
{
	uint size;
	ByteListElement *elements;
} ByteList;


#define string 



#endif /* DATA_TYPES */
