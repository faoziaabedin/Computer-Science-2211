/* reminder.h
   Faozia Abedin
   251358251
*/
#ifndef REMINDER_H
#define REMINDER_H

#define MAX_STR_LEN 100

// Node structure for linked list of reminders
struct Node {
    char reminder[MAX_STR_LEN];
    struct Node *next;
};

// Month structure containing reminders for each day
struct Month {
    int month_idx;               // Index of the month (0 = January, 11 = December)
    int month_days;              // Number of days in the month
    int start_day;               // Starting day of the week (0 = Sunday, 6 = Saturday)
    struct Node *reminders[31];  // Array of linked lists for reminders
};


// Initializes the current month with start day and number of days
void initializeMonth(struct Month *month);

// Prints the calendar for the current month with reminders
void printCalendar(struct Month *month);

#endif
