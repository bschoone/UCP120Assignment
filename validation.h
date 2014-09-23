#ifndef _VAL_H_
#define _VAL_H_

#include "readCal.h"

int validEvent(CalEvent*);
int validDate(int, int, int);
int checkLeapYear(int);
int validTime(int,int);
int validDuration(int);

#endif
