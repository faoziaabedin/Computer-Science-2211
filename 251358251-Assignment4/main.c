/* 251358251-Assignment4
   Faozia Abedin (fabedin4)

   This file handles user interaction and program flow. 
   It initializes the November calendar and enters a loop where it prompts the user to enter reminders for specific days. 
   Each reminder is stored using insert_to_calendar, and the updated calendar is displayed after each entry. 
   The program exits when the user enters 0 for the day.
*/
#include "reminder.h"

// Declare and initialize the November variable
struct Month November = {30, 6, {""}, {false}}; // November with 30 days, starts on Saturday

int main() {
    char reminder[MAX_STR_LEN];
    int day;

    while (1) {
        // Read the reminder from the user
        day = Reminder(reminder, MAX_STR_LEN);
        
        if (day == 0) {
            // Exit condition when user enters 0
            break;
        }

        // Check if the input is valid before inserting
        if (day > 0 && day <= November.month_days) {
            insert_calendar(day, reminder); // Insert the reminder into the calendar
            print_calendar(); // Display the updated calendar
        } else {
            printf("Invalid day!. Please enter a day between 1 and %d.\n", November.month_days);
        }
    }

    return 0;
}
