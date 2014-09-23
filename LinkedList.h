#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_


/********************************
* LinkedListNode Struct
* Contains a pointer to another linked list node and a void pointer to some sort of data
********************************/
typedef struct LinkedListNode { void *data; struct LinkedListNode *next;} LinkedListNode;

/********************************
* LinkedList Struct
* Contains a pointer to a linked list node
********************************/

typedef struct LinkedList { LinkedListNode *head; } LinkedList;

LinkedList* createLinkedList();
void insertNodeStart(LinkedList *, void* );
void insertNodeEnd(LinkedList *, void* );
void insertNElement(LinkedList*, int, void*);
LinkedListNode* removeFirstElement(LinkedList *);
LinkedListNode* removeLastElement(LinkedList *);
LinkedListNode* removeNElement(LinkedList*, int);
LinkedListNode* findNElement(LinkedList*, int);
int getLength(LinkedList *);
void freeLinkedList(LinkedList*);

#endif
