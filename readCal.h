#ifndef _READCAL_H_
#define _READCAL_H_

#include "LinkedList.h"


/********************************
* Date Struct
* Contains three ints that represent date, month, year of an event
********************************/

typedef struct Date {int day; int month; int year;} Date;

/********************************
* Time Struct
* Contains two ints that represent hours and minutes of an event
********************************/

typedef struct Time {int hours; int minutes;} Time;
/********************************
* CallEvent Struct
* Contains two char* and pointers to a Date struct and a Time struct
* used to store an events details
********************************/

typedef struct CalEvent { Date date;  Time time; int duration; char* event; char* location;} CalEvent;

LinkedList* createEvents(char*);
void loadEvents(char*, LinkedList*); 
int nextLineBlank(FILE*);
char* printLinkedList(LinkedList*);
void saveToFile(char*, void*);
void removeNewLine(char*); 
void addEvent(char**, void*); 

#endif
