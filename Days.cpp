// ******************************************************************
//
// Days.cpp
// By: Nathan Blue
// Final Project
//  10/18/16
// Purpose: Implementation of the Days Class
// ******************************************************************
#include "Days.h"

Days::Days()
{
	days = 0;
}

int Days::getDays()
{
	return days;
}

void Days::incrementDay()
{
	days = days + 1;
}

