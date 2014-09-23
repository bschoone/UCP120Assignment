#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gui.h"
#include "LinkedList.h"
#include "GoogleCalendar.h"
#include "readCal.h"

int main(int argc, char *argv[])
{
	char* output = NULL;
	
	AppData *calData;
	calData = (AppData*)malloc(sizeof(AppData));
		
	calData->appWindow = createWindow("Google Calendar");
	/*Create an initial empty LinkedList*/
	calData->eventList = createLinkedList();
	
	/*Set up the buttons and their calls*/	
	addButton(calData->appWindow, "Load a calendar from file", (&loadCal), (void*)calData);
	addButton(calData->appWindow, "Save the current calendar to file", (&saveCal), (void*)calData);
	addButton(calData->appWindow, "Add a calendar event", (&addCal), (void*)calData);
	addButton(calData->appWindow, "Edit a calander event", (&editCal), (void*)calData);
	addButton(calData->appWindow, "Delete a calendar event", (&removeCal), (void*)calData);
	setText(calData->appWindow, "Welcome to Google Calendar\n---------------------------\nPlease pick a button on the side to continue");
	
	/*If given parameter, load it*/
	if(argc==2)
	{
		loadEvents(argv[1], calData->eventList);
		/*Set up the one string to print to the screen*/
		output = printLinkedList(calData->eventList);
		/*Set the screen text with said returned string*/
		setText(calData->appWindow, output);
		free(output);
	}
	runGUI(calData->appWindow);
	freeWindow(calData->appWindow);
	freeData(calData->eventList);
	freeLinkedList(calData->eventList);
	return(0);
}

/*
Method Name: loadCal
Parameters: AppData typecast to a void pointer
Returns: nothing
Method Desc: sets up the dialog box with textfeilds and calls loadEvents
*/
void loadCal(void* appData)
{
	char dialogTitle[] = "Load a Calendar";
	int ans, nInputs = 1;
	InputProperties *properties = NULL;
	char **inputs = NULL;
	char* output;
	Window* currWindow = ((AppData*)appData)->appWindow;
	
	inputs = mallocInputs(nInputs);
	strcpy(inputs[0], "Filename");
	
	/*Free the current linked list*
	freeLinkedList( (((AppData*)appData)->eventList) );*/
	
	/*Malloc an array of InputProperties structs and sets up each structs fields */
	
	properties = mallocProperties(nInputs);
	strcpy(properties[0].label, "Enter the name of the file to load from");
	
	/*run the dialog box*/
	ans = dialogBox(currWindow, dialogTitle, nInputs, properties, inputs);
	
	/*check if the user hit OK, if so, do the if statement*/
	if(ans!=0)
	{
		/*create the linked list by passing createEvents the file name*/
		
		loadEvents( inputs[0], (((AppData*)appData)->eventList) );
		if( (((AppData*)appData)->eventList)->head !=NULL)
		{
			/*Set up the one string to print to the screen*/
			output = printLinkedList((((AppData*)appData)->eventList));
			/*Set the screen text with said returned string*/
			setText(currWindow, output);
		}
	}
	freeProperties(nInputs, properties);
	freeInputs(nInputs, inputs);
}

/*
Method Name: saveCal
Parameters: AppData typecast to a void pointer
Returns:nothing
Method Desc: Sets up the dialog box with textfeilds and displays it, then if the user hits okay, it will call saveToFile*/

void saveCal(void* appData)
{
	char dialogTitle[] = "Save a Calendar";
	int ans, nInputs = 1;
	InputProperties *properties = NULL;
	char **inputs = NULL;
	Window* currWindow = ((AppData*)appData)->appWindow;
	
	inputs = mallocInputs(nInputs);
	strcpy(inputs[0], "Filename");
	
	properties = mallocProperties(nInputs);
	strcpy(properties[0].label, "Enter the name of the file to save to");
	
	ans = dialogBox(currWindow, dialogTitle, nInputs, properties, inputs);

	if(ans!=0)
	{
		if( (((AppData*)appData)->eventList->head) == NULL)
		{
			messageBox( (((AppData*)appData)->appWindow), "No Calendar to Save");
		}
		else
		{
			saveToFile(inputs[0], appData);
		}
	}
	freeProperties(nInputs, properties);
	freeInputs(nInputs, inputs);
}


/*********************************************
* Method Name: addCal
* Parameters: void* (A CalEvent)
* Returns: nothing
* Method Desc: Throws up a dialog box in which the user can add the fields
				of the event, then the event gets inserted into the LinkedList
				if it is valid
*********************************************/
void addCal(void* appData)
{
	char dialogTitle[] = "Add Event", *output;
	int ans, nInputs = 8;
	InputProperties *properties = NULL;
	char **inputs = NULL;
	Window* currWindow = ((AppData*)appData)->appWindow;

	inputs = mallocInputs(nInputs);
	properties = mallocProperties(nInputs);
	setEventInfoProperties(properties);
	
	ans = dialogBox(currWindow, dialogTitle, nInputs, properties, inputs);

	if(ans!=0)
	{
		addEvent(inputs, appData);
		/*Set up the one string to print to the screen*/
		output = printLinkedList(((AppData*)appData)->eventList);
		/*Set the screen text with said returned string*/
		setText(currWindow, output);
	}
	freeProperties(nInputs, properties);
	freeInputs(nInputs, inputs);
}


/*********************************************
* Method Name: editCal
* Parameters: void* 
* Returns: nothing
* Method Desc: edits an event
*				Creates a temp event and stores the new values in it
				Checks if it is valid, if it is insert in in the end of the linhked list
				If its not, insert the old one
				Free whichever isnt used.
*********************************************/
void editCal(void* appData)
{
	char dialogTitle[] = "Edit Event", *eventFormat, **inputs = NULL, *output = NULL;
	int ans, nInputs = 1, ii, size, placeInList;
	InputProperties *properties = NULL;
	Window* currWindow;
	LinkedListNode* returnedNode, *tempNode;
	CalEvent* tempEvent;
	
	
	/*Malloc and set initial values*/
	currWindow = ((AppData*)appData)->appWindow;
	size = getLength( ((AppData*)appData)->eventList);
	size += MAX_LENGTH;
	
	eventFormat = (char*)malloc(MAX_LENGTH*sizeof(char));
	output = (char*)malloc(size*sizeof(char));
	
	tempEvent = (CalEvent*)malloc(sizeof(CalEvent));
	tempEvent->event = (char*)malloc(MAX_LENGTH*sizeof(char));
	tempEvent->location = (char*)malloc(MAX_LENGTH*sizeof(char));
	
	properties = mallocProperties(nInputs);
	inputs = mallocInputs(nInputs);
	strcpy(properties[0].label, "Which event do you want to edit?\n");
	
	tempNode = ((AppData*)appData)->eventList->head;
	
	for(ii=0; ii < (getLength( ((AppData*)appData)->eventList) ); ii++)
	{
		/*USE THIS TO PRINT NUMBER AND EVENT TO CHOOSE*/
		sprintf(eventFormat, "%d: %s\n", (ii+1),  ((CalEvent*)tempNode->data)->event);
		strcat(properties[0].label, eventFormat);
		tempNode = tempNode->next;
	}
	
	ans = dialogBox(currWindow, dialogTitle, nInputs, properties, inputs);
	/*Check if event was a valid choice, if it is then edit event chosen*/
	if(ans!=0)
	{
		if( (atoi(inputs[0])) > (getLength( ((AppData*)appData)->eventList) ) || (atoi(inputs[0])) < 1 )
		{
			messageBox( (((AppData*)appData)->appWindow), "Event was Invalid, Please check your inputs");
		}
		else
		{	
			placeInList = (atoi(inputs[0]));
			returnedNode = removeNElement((((AppData*)appData)->eventList), placeInList);
			
			freeInputs(nInputs, inputs);
			freeProperties(nInputs, properties);	

			inputs = mallocInputs(8);
			properties = mallocProperties(8);
			setEventInfoProperties(properties);
			setInputs( inputs, ((CalEvent*)returnedNode->data) );
			
			ans = dialogBox(currWindow, dialogTitle, 8, properties, inputs);
			if(ans!=0)
			{
				updateData(inputs, tempEvent);
				if( validEvent(tempEvent)==1)
				{
				
					updateData(inputs,returnedNode->data );
					insertNodeEnd( ((AppData*)appData)->eventList, returnedNode->data);
					/*Set up the one string to print to the screen*/
					output = printLinkedList(((AppData*)appData)->eventList);
					/*Set the screen text with said returned string*/
					setText(currWindow, output);
				}
				else
				{
					insertNodeEnd( ((AppData*)appData)->eventList, returnedNode->data);
					/*Set up the one string to print to the screen*/
					output = printLinkedList(((AppData*)appData)->eventList);
					/*Set the screen text with said returned string*/
					setText(currWindow, output);
				}	
			}
		}
	}
	free(output);
	free(eventFormat);
}

/*********************************************
* Method Name: removeCal
* Parameters: void* (CalEvent)
* Returns: nothing
* Method Desc: Let the user choose and event and then delete and free it
*********************************************/
void removeCal(void* appData)
{
	char dialogTitle[] = "Remove Event", *eventFormat, **inputs = NULL;
	int ans, nInputs = 1, ii, size;
	InputProperties *properties = NULL;
	Window* currWindow;
	LinkedListNode* returnedNode, *tempNode;
	void* currEvent;
	
	currWindow = ((AppData*)appData)->appWindow;
	
	
	size = getLength( ((AppData*)appData)->eventList);
	size += MAX_LENGTH;
	
	
	eventFormat = (char*)malloc(size*sizeof(char));
	
	properties = mallocProperties(nInputs);
	inputs = mallocInputs(nInputs);
	
	strcpy(properties[0].label, "Which event do you want to delete?\n");
	
	tempNode = ((AppData*)appData)->eventList->head;
	for(ii=0; ii < (getLength( ((AppData*)appData)->eventList) ); ii++)
	{
		currEvent = tempNode->data;
		/*USE THIS TO PRINT NUMBER AND EVENT TO CHOOSE*/
		sprintf(eventFormat, "%d: %s\n", (ii+1),  ((CalEvent*)currEvent)->event);
		strcat(properties[0].label, eventFormat);

		tempNode = tempNode->next;
	}
	
	ans = dialogBox(currWindow, dialogTitle, nInputs, properties, inputs);
	
	if(ans!=0)
	{
		if( (atoi(inputs[0])) > (getLength( ((AppData*)appData)->eventList) ) )
		{
			messageBox( (((AppData*)appData)->appWindow), "Event Doesnt Exist");
		}
		else
		{
			returnedNode = removeNElement( (((AppData*)appData)->eventList), (atoi(inputs[0])) );
			free(returnedNode);
			setText((((AppData*)appData)->appWindow), (printLinkedList(((AppData*)appData)->eventList)) );
		}
	}
}

/*********************************************
* Method Name: setEventInfoProperties
* Parameters: InputProperties*
* Returns: void
* Method Desc: Set the default values of input properties
*********************************************/
void setEventInfoProperties(InputProperties* properties)
{

	strcpy(properties[0].label, "Whats the name of the event?");
	strcpy(properties[1].label, "Where does the event take place");
	strcpy(properties[2].label, "Day of the event (DD)");
	strcpy(properties[3].label, "Month of the event (MM)");
	strcpy(properties[4].label, "Year of the event (YYYY)");
	strcpy(properties[5].label, "How long does the event go for? (in minutes)");
	strcpy(properties[6].label, "Hours (24 Hour Time)");
	strcpy(properties[7].label, "Minutes");

}

/*********************************************
* Method Name: mallocInputs
* Parameters: int
* Returns: char**
* Method Desc: malloc a 2d array of char*
*********************************************/
char** mallocInputs(int nInputs)
{	
	char** inputs = NULL;
	int ii;
	
	inputs = (char**)malloc(nInputs*sizeof(char*));

	/*Malloc each textfield and label*/
	for(ii=0; ii<nInputs; ii++)
	{	
		inputs[ii] = (char*)malloc((MAX_LENGTH+1)*sizeof(char));
		strcpy(inputs[ii], "");
	}


	return inputs;
}

/*********************************************
* Method Name: setInputs
* Parameters: char**, CalEvent*
* Returns: nothing
* Method Desc: sets the inputs of the text feilds to that of the event being edited
*********************************************/
void setInputs(char** inputs, CalEvent* eventData)
{
		strcpy(inputs[0], eventData->event);
		strcpy(inputs[1], eventData->location);
		sprintf(inputs[2], "%d", eventData->date.day);
		sprintf(inputs[3], "%d", eventData->date.month);
		sprintf(inputs[4], "%d", eventData->date.year);
		sprintf(inputs[5], "%d", eventData->duration);
		sprintf(inputs[6], "%d", eventData->time.hours);
		sprintf(inputs[7], "%d", eventData->time.minutes);
		
}

/*********************************************
* Method Name: updateData
* Parameters: char**, CalEvent*
* Returns: nothing
* Method Desc: updates the CalEvent with the inputs from the user
*********************************************/
void updateData(char** inputs, CalEvent* eventData)
{
		eventData->event = inputs[0];
		eventData->location = inputs[1];
		eventData->date.day = atoi(inputs[2]);
		eventData->date.month = atoi(inputs[3]);
		eventData->date.year = atoi(inputs[4]);
		eventData->duration = atoi(inputs[5]);
		eventData->time.hours = atoi(inputs[6]); 
		eventData->time.minutes = atoi(inputs[7]);
		
}

/*********************************************
* Method Name: freeInputs
* Parameters: int, char**
* Returns: nothing
* Method Desc: frees inputs
*********************************************/
void freeInputs(int nInputs, char** inputs)
{	
	int ii;
	
	/*Malloc each textfield and label*/
	for(ii=0; ii<nInputs; ii++)
	{	
		free(inputs[ii]);;
	}
	free(inputs);
}

/*********************************************
* Method Name: mallocProperties
* Parameters: nInputs
* Returns: InputProperties*
* Method Desc: malloc memory for input properties
*********************************************/
InputProperties* mallocProperties(int nInputs)
{	
	int ii = 0;
	InputProperties* properties = (InputProperties*)malloc(nInputs*sizeof(InputProperties));
	
	for(ii=0; ii<nInputs; ii++)
	{
		properties[ii].label = (char*)malloc((MAX_LENGTH*50)*sizeof(char));
		properties[ii].maxLength = MAX_LENGTH;
		properties[ii].isMultiLine = 0;
	}	
	
	return properties;
}

/*********************************************
* Method Name: freeProperties
* Parameters: int, InputProperties
* Returns: nothing
* Method Desc: frees properties
*********************************************/
void freeProperties(int nInputs, InputProperties* properties)
{	
	int ii = 0;
	
	for(ii=0; ii<nInputs; ii++)
	{		
		free(properties[ii].label);
		
	}	
	free(properties);
	
}

void freeData(LinkedList* list)
{
	LinkedListNode* tempNode;
	
	tempNode = list->head;
	
	while (tempNode !=NULL)
	{
		free( ((CalEvent*)(tempNode->data))->event );
		free( (CalEvent*)(tempNode->data) );
		tempNode = tempNode->next;
	}


}
