#ifndef _GOOGLE_H_
#define _GOOGLE_H_

#include "readCal.h"
#include "gui.h"
#include "validation.h"

#define FALSE 0
#define TRUE !FALSE
#define MAX_LENGTH 100

/**************************************************************
* AppData Struct
* Contains a Window and the Linked List of the calendar
* Used to pass around the LinkedList and the GUI windows into functions used by
* the buttons of the GUI as the can only take a single parameter and only a void* parameter
**************************************************************/
typedef struct  {Window* appWindow; LinkedList* eventList;} AppData;

void openMessageBox(void*);
void openDialogBox(void*);
void setScreenText(void*);
void loadCal(void*);
void saveCal(void*);
void addCal(void*);
void editCal();
void removeCal(void*);
void setEventInfoProperties(InputProperties*);
InputProperties* mallocProperties(int);
char** mallocInputs(int);

void freeInputs(int, char**);
void freeProperties(int, InputProperties*);

void setInputs(char**, CalEvent*);
void updateData(char**, CalEvent*);

void freeData(LinkedList*);

#endif
