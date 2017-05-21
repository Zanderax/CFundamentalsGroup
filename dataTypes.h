#ifndef DATA_TYPES
#define DATA_TYPES

typedef char byte;
#define MAX_NAME_SIZE 50

typedef unsigned int uint;

typedef int bool;

#define TRUE 1
#define FALSE 0

#define dataSize 40

typedef struct {
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

struct Node {
	uint data;
	byte count;
	Node *left;
	Node *right;
};

typedef struct {
	byte data;
	uint count;
} ByteListElement;

typedef struct {
	uint size;
	ByteListElement *elements;
} ByteList;
#endif /* DATA_TYPES */
