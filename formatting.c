#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "formatting.h"

/*********************************************
* File Name: formatting.c  
* File Desc: a bunch of methods for formatting the print out of an Event.
			All methods should explain themselves hence lack of commenting in places 
*********************************************/

/*Takes a month number and returns the month in words*/
char* formatMonth(int month)
{
	char* months[13] = {"","Jan", "Feb", "Mar", "Apr","May","Jun","Jul","Aug","Sep","Oct", "Nov", "Dec"};
	
	return months[(month)];
 
}

/*Takes in a location, if there is a location add a @ at the front else return event*/
char* formatLocation(char* location)
{
	char* locationFormatting;
	locationFormatting = (char*)malloc(MAX_LENGTH*sizeof(char));
	
	strcpy(locationFormatting, "");
	if(strcmp(location, "") != 0)
	{
		sprintf(locationFormatting, "@ %s", location);
	}	
	
	return locationFormatting;
}

/*Turn 24hour time into 12 hour time and add am/pm to the end*/
char* formatTime(int hours, int minutes)
{
	int time[13]= {0,1,2,3,4,5,6,7,8,9,10,11,12};
	char* timeFormatting;
	
	timeFormatting = (char*)malloc(MAX_LENGTH*sizeof(char));
	strcpy(timeFormatting, "");
	
	if(hours>12 && hours<=24)
	{
		sprintf(timeFormatting, "%02d:%02dpm", time[(hours-12)], minutes);
	}
	else
	{
		sprintf(timeFormatting, "%02d:%02dam", time[hours], minutes);
	}
	
	return timeFormatting;
	
}

/*Take a duration in minutes, turn into hours and minutes*/
char* formatDuration(int duration)
{
	char* durationFormatting, *temp;
	int hours, minutes;
	
	durationFormatting = (char*)malloc(MAX_LENGTH*sizeof(char));
	temp = (char*)malloc(MAX_LENGTH*sizeof(char));
	
	
	hours = duration/60;
	minutes = duration%60;
	
	strcpy(durationFormatting, "");
	strcpy(temp, "");
	
	if(hours == 1)
	{
		sprintf(temp, "%d hour, ", hours);
		strcat(durationFormatting, temp);
	}
	else if(hours > 1)
	{
		sprintf(temp, "%d hours, ", hours);
		strcat(durationFormatting, temp);
	}	
	
	
	if(minutes == 1)
	{
		sprintf(temp, "%d minute", minutes);
		strcat(durationFormatting, temp);
	}
	else if(minutes > 1)
	{
		sprintf(temp, "%d minutes", minutes);
		strcat(durationFormatting, temp);
	}
	
	free(temp);
	return durationFormatting;
	

}
