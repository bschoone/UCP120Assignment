#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "readCal.h"
#include "gui.h"
#include "GoogleCalendar.h"
#include "validation.h"
#include "formatting.h"

LinkedList* createEvents(char* fileName)
{
	LinkedList *eventList;
	eventList = createLinkedList();
	loadEvents(fileName, eventList);
	return eventList;

}

/*****************************************************************
* Method Name: loadEvents
* Parameters: takes in a file name and a linked list pointer
* Returns:nothing
* Method Desc: creates a CalEvent, reads from the file and populates it, then inserts a
*				LinkedListNode that points to said CalEvent
*****************************************************************/
void loadEvents(char* fileName, LinkedList* eventList)
{
	FILE *read = fopen(fileName, "r");
	CalEvent *testEvent;
	
	/*Check if file has been opened*/
	if(read == NULL)
	{
		/*IF IT DIDNT OPEN DO NOTHING*/
	}
	else
	{		
		/*Free the current linked list and data*/
		freeLinkedList( (eventList) );
		
		while(!feof(read))
		{
			/*Malloc the CalEvent to Populate*/
			testEvent = (CalEvent*)malloc(sizeof(CalEvent));
			testEvent->event = (char*)malloc(MAX_LENGTH*sizeof(char));
			testEvent->location = (char*)malloc(MAX_LENGTH*sizeof(char));
			/*Read from the file and insert into the CalEvent*/
			
			fscanf(read, "%d-%d-%d %d:%d %d ", &(testEvent->date.year), &(testEvent->date.month), &(testEvent->date.day), &(testEvent->time.hours), &(testEvent->time.minutes), &(testEvent->duration) );
			
			/* Read the event */
				fgets(testEvent->event, MAX_LENGTH, read);
				removeNewLine(testEvent->event); 

				/*Check if next line has a location or not, if not, make event "" */
				if(nextLineBlank(read) == 1)
				{
					testEvent->location = "";
				}
				/*if the is an event, read it and then remove the \n it includes*/
				if(nextLineBlank(read) == 2)
				{	
					fgets(testEvent->location, MAX_LENGTH, read);
					removeNewLine(testEvent->location);
				}
				/*Insert a new node and its data points to the current data*/
				if( validEvent(testEvent) == 1)
				{
					insertNodeEnd(eventList, (void*)testEvent);
				}	
		}
	}
}

/*********************************************
* Method Name: printLinkedList
* Parameters: LinkedList
* Returns: String
* Method Desc: Takes the EventList, formats a string to print to the GUIs main screen
*				returns said string
*********************************************/

char* printLinkedList(LinkedList* list)
{

	LinkedListNode* currNd;
	CalEvent *currEvent = NULL;
	char *output = NULL, *eventFormat = NULL, *location = NULL, *month = NULL, *time = NULL, *duration = NULL;
	int size;
	
	size = (getLength(list)) * (MAX_LENGTH*3);
	eventFormat = (char*)malloc(size*sizeof(char));
	output = (char*)malloc(size*sizeof(char));
	strcpy(output, "");

	currNd = list->head;
	if(currNd != NULL)
	{	
		do
		{	
			currEvent = (CalEvent*)(currNd->data);
			
			/*Format the string for printing to file*/
			location = formatLocation(currEvent->location);
			month = formatMonth(currEvent->date.month);
			time = formatTime(currEvent->time.hours, currEvent->time.minutes);
			duration = formatDuration(currEvent->duration);
			
			sprintf(eventFormat, "%s %s (%s)\n%d %s %d, %s\n---\n\n", currEvent->event, location, duration, currEvent->date.day, month, currEvent->date.year, time);
			
			/*copy formatted string to output and go to next node*/
			strcat(output, eventFormat);
			currNd = currNd->next;
			
			
		}
		while(currNd != NULL);
		
	}
	free(eventFormat);
	return output;
}

/*********************************************
* Method Name: saveToFile 
* Parameters: string (Name of the file to open, void* (CalEvent Struct)
* Returns: nothing
* Method Desc: opens a file to save to, formats a string to print to file and
*				then appends to file
*********************************************/


void saveToFile(char* fileName, void* appData)
{
	LinkedListNode* currNd;
	char *eventFormat = NULL;
	int size;
	FILE *save = fopen(fileName, "w");
	CalEvent *currEvent = NULL;
	
	size = (getLength( ((AppData*)appData)->eventList))*(MAX_LENGTH*3);

	/*size = size*(MAX_LENGTH*3);*/
	eventFormat = (char*)malloc(size*sizeof(char));
	currNd = ((AppData*)appData)->eventList->head;
	
	/*Make sure the event list isnt empty*/
	if(currNd != NULL)
	{	
		do
		{
			currEvent = (CalEvent*)(currNd->data);
			/*format the string to be whats required*/
			sprintf(eventFormat, "%d-%02d-%02d %02d:%02d %d %s\n%s\n\n", currEvent->date.year, currEvent->date.month, currEvent->date.day, currEvent->time.hours, currEvent->time.minutes, currEvent->duration, currEvent->event, currEvent->location);
		
			fputs(eventFormat, save);
			currNd = currNd->next;
		}
		while(currNd != NULL);
	}
	fclose(save);
	free(eventFormat);
}



/*********************************************
* Method Name: addEvent 
* Parameters: Array of strings, void* (of a CalEvent)
* Returns: nothing
* Method Desc: mallocs a new event and inserts it at the end of the event list
*********************************************/

void addEvent(char** inputs, void* appData)
{
	CalEvent* newEvent;
	int isValid;
	
	newEvent = (CalEvent*)malloc(sizeof(CalEvent));
	newEvent->event = (char*)malloc(MAX_LENGTH*sizeof(char));
	newEvent->location = (char*)malloc(MAX_LENGTH*sizeof(char));
	
	strcpy(newEvent->event, inputs[0]);
	strcpy(newEvent->location, inputs[1]);
	newEvent->date.day = atoi(inputs[2]);
	newEvent->date.month = atoi(inputs[3]);
	newEvent->date.year = atoi(inputs[4]);
	newEvent->duration = atoi(inputs[5]);
	newEvent->time.hours = atoi(inputs[6]);
	newEvent->time.minutes = atoi(inputs[7]);
	
	/*Validate the event, if not valid, show a messageBox if not and dont add*/
	isValid = validEvent(newEvent);
	
	if(isValid == 1)
	{
		insertNodeEnd( ((AppData*)appData)->eventList ,(void*)newEvent);
	}
	else
	{
		messageBox( (((AppData*)appData)->appWindow), "Event was invalid");
	}
}

/*
Method Name: nextLineBlank
Parameters: FILE pointer
Returns: int
Method Desc: checks and sees if the next line contains an event or a blank line
*/

int nextLineBlank(FILE *fin)
{
	char temp;
	temp = getc(fin);
	if( temp=='\n')
	{
		ungetc(temp, fin);
		return 1;
	}
	else
	{
		ungetc(temp, fin);
    	return 2;
    }
} 

/*
Method Name: removeNewLine
Parameters:string
Returns:nothing
Method Desc:edits the string passed by reference to remove the new line char
*/
void removeNewLine(char *str) 
{
    size_t len = strlen(str);
    if (str[len-1] == '\n') 
    {
        str[len-1] = '\0';
    }
}

