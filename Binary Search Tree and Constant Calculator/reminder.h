#ifndef REMINDER_H
#define REMINDER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STR_LEN 100

struct Month{
	int month_days;
	int start_day;
    char reminder_str[31][MAX_STR_LEN]; 
	bool reminders[31]; 
};

extern struct Month November ; 

/*
Takes a reminder string and a day number and inserts the reminder into the calendar.
Also, sets the reminder flag to true for that day.
 */
void insert_to_calendar(int day, const char* value) ;

/*
Takes a char array and its length and reads a reminder from the user.
Returns the day number.
 */
int read_reminder(char *str, int n) ;

/*
Prints the calendar and the reminders for each day.	
 */
void print_calendar() ;

#endif