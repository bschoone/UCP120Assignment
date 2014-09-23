#include <stdio.h>
#include <stdlib.h>

#include "validation.h"

/*********************************************
* Method Name:ValidEvent 
* Parameters: CalEvent
* Returns: int
* Method Desc: Calls a range of funtions to check certain 
*				aspects of the event and return 1 if valid
*				and 0 if not 
*********************************************/
int validEvent(CalEvent* currEvent)
{
	int isValid;
	
	if( (validDate(currEvent->date.day, currEvent->date.month, currEvent->date.year)) == 1 && (validTime(currEvent->time.hours, currEvent->time.minutes)) == 1 && (validDuration(currEvent->duration)) == 1)
		{
			isValid = 1;
		}
	else
	{
		isValid = 0;
	}
	
	return isValid;
}

/*Checks if the date is valid*/
int validDate(int day, int month, int year)
{
	int valid = 1;
	int month_length[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if ( checkLeapYear(year) )
		month_length[1] = 29;
		/*  29 days in February in a leap year (including year 2000)*/

	if ( month < 1 || month > 12 )
		valid = 0;
	else if ( day < 1 || day > month_length[month-1] )
		valid = 0;

	return (valid);
}


/*Checks if leap year*/
int checkLeapYear(int year)
{
	int result;

	if ( (year%4) != 0 )           
		result = 0;            
	else if ( (year%400) == 0 )    
		result = 1;             
	else if ( (year%100) == 0 )    
		result = 0;            
	else                           
		result = 1;             

	return ( result );
}

/*Checks for valid 24hour time*/
int validTime(int hours, int minutes)
{
	int valid =1;
	
	if(hours>23 || hours<0){
		valid = 0;}
	if(minutes>59 || minutes<0){
		valid = 0;}
	
	return valid;
}

/*Checks duration isnt negative*/
int validDuration(int duration)
{
	int valid = 1;
	
	if(duration<0){
		valid = 0;}
		
	return valid;
}


