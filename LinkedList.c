#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

LinkedList* createLinkedList()
{	
	LinkedList *list;

	list = (LinkedList*)malloc(sizeof(LinkedList));
	list->head = NULL;
	return list;
}

void insertNodeStart(LinkedList *list, void* value)
{
	LinkedListNode *newNode;

	newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	
	newNode->next = list->head;
	list->head = newNode;
	
	newNode->data = value;
	
}

void insertNodeEnd(LinkedList *list, void* value)
{
	LinkedListNode *newNode = NULL, *tempNode = NULL;
	
	newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
	newNode->next = NULL;
	newNode->data = value;
	
	tempNode = list->head;
	
	/*Check if the list is empty*/	
	if(list->head == NULL)
	{
		list->head = newNode;
	}
	/*If it is not, then itterate over the list*/
	else{
	while( (tempNode->next) != NULL)
	{
		tempNode = tempNode->next;
	}

	tempNode->next = newNode;
	}
}

void insertNElement(LinkedList *list, int n, void* value)
{
	int ii;
	LinkedListNode *currNode, *tempNode, *insertNode;
	
	
	tempNode = list->head;
	currNode = tempNode->next;
	
	if(n == 1)
	{
		insertNodeStart(list, value);
	}
	else if(n == getLength(list) )
	{
		insertNodeEnd(list, value);
	}
	else
	{
		
		for(ii=1; ii <= n-2; ii++)
		{
	 		tempNode = currNode;
	 		currNode = tempNode->next;	
		}
		insertNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
		insertNode->data = value;	
		insertNode->next = tempNode;
		currNode->next = insertNode;
		
	}

}


LinkedListNode* removeLastElement(LinkedList *list)
{
	LinkedListNode *tempNodeOne, *tempNodeTwo;
	
	tempNodeOne = list->head;
	tempNodeTwo = tempNodeOne->next;
	
	/*Check if the list is empty*/	
	if(list->head == NULL)
	{
		
	}
	/*If it is not, then itterate over the list*/
	else
	{
		while( (tempNodeTwo->next) != NULL)
		{
			tempNodeOne = tempNodeTwo;
			tempNodeTwo = tempNodeOne->next;
		}
			tempNodeOne->next = NULL;
	}
	return tempNodeTwo;
	
}


LinkedListNode* removeFirstElement(LinkedList *list)
{
	LinkedListNode *temp = NULL;
	
	temp = list->head;
	list->head = temp->next;
	
	return temp; 
	
}

LinkedListNode* removeNElement(LinkedList *list, int n)
{
	int ii;
	LinkedListNode *currNode, *tempNode, *removedNode;
	
	tempNode = list->head;
	currNode = tempNode->next;
	
	if(n == 1)
	{
		removedNode = removeFirstElement(list);
	}
	else if(n == getLength(list) )
	{
		removedNode = removeLastElement(list);
	}
	else
	{
		
		for(ii=1; ii <= n-2; ii++)
		{
	 		tempNode = currNode;
	 		currNode = tempNode->next;	
		}
		removedNode = currNode;
		tempNode->next = currNode->next;
	}
	return removedNode;
}



LinkedListNode* findNElement(LinkedList *list, int n)
{
	int ii;
	LinkedListNode *currNode, *tempNode, *foundNode;
	
	tempNode = list->head;
	currNode = tempNode->next;
	
	if(n-2 == (-1))
	{
		foundNode = tempNode;
	}
	else
	{
		for(ii=1; ii <= n-2; ii++)
		{
 			tempNode = currNode;
 			currNode = tempNode->next;	
		}
			foundNode = currNode;
	}
	return foundNode;
}




int getLength(LinkedList *list)
{

	int length = 0;
	LinkedListNode *current;
	
	current = list->head;
	while(current != NULL) 
	{
		length++;
		current = (*current).next;
	}
	
	return length;
}


void freeLinkedList(LinkedList *list) 
{
	LinkedListNode *node, *nextNode;
	node = list->head;
	while(node != NULL) 
	{
		nextNode = (node->next);
		free(node->data); /* Maybe! */
		free(node);
		node = nextNode;
	}
	list->head=NULL;
}

