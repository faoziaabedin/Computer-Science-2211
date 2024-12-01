/* 251358251-Assignment4
   Faozia Abedin (fabedin4)

   This file contains the core functionality for managing reminders in the calendar. 
   It includes functions to insert a reminder (insert_to_calendar), read a reminder from user input (read_reminder), and print the November calendar with marked reminder days (print_calendar). 
   The insert_to_calendar function stores reminders for specific days, while print_calendar displays the month layout and lists reminders for easy reference.
*/
#include "reminder.h"

// Global variable declaration from main.c
extern struct Month November;

// Inserts a reminder into the calendar and marks the reminder flag
void insert_calendar(int day, const char *value) {
    // Check if the day is within valid range for the month
    if (day < 1 || day > November.month_days) {
        printf("Invalid day!.\n");
        return;
    }
    
    // Copy the reminder text into the reminder_str array for the specified day
    // snprintf ensures the string fits within MAX_STR_LEN and adds a null terminator
    snprintf(November.reminder_str[day - 1], MAX_STR_LEN, "%s", value);

    // Set the reminder flag to true for this day to indicate a reminder exists
    November.reminders[day - 1] = true;
}

// Reads a reminder from the user, storing it in the provided string, and returns the day number
int Reminder(char *str, int n) {
    int day;
    printf("____________________________________\n");
    printf("Enter day and reminder (0 to quit): ");
    
    // Read the day number from the user
    scanf("%d", &day);
    getchar(); // Clear newline character left in the input buffer by scanf

    // Check if the day is within the valid range (0 to exit, or 1-30)
    if (day < 0 || day > 30) {
        printf("Invalid day.\n");
        return -1;
    }
    if (day == 0) {
        return 0; // Exit condition if the user enters 0
    }

    // Read the reminder text from the user and store it in str
    fgets(str, n, stdin);
    str[strcspn(str, "\n")] = '\0'; // Remove the newline character at the end of the string

    return day; // Return the day number
}

// Prints the November calendar with reminder days marked and lists reminders
void printing_calendar() {
    // Print the header for the calendar with days of the week
    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    int day = 1;
    int weekday = November.start_day;
    int i = 0;

    // Print leading spaces for the start day
    for (int j = 0; j < weekday; j++) {
        printf("     ");
    }

    // Print the days of the month with reminders
    while (day <= November.month_days) {
        if (November.reminders[day - 1]) {
            printf(" (%2d)", day); // Display days with reminders in parentheses
        } else {
            printf("  %2d ", day); // Display regular days with padding for alignment
        }
        
        // Move to the next line at the end of each week (after every 7 days)
        if ((i + weekday + 1) % 7 == 0) {
            printf("\n");
        }
        
        day++;
        i++;
    }
    printf("\n\nReminders:\n");

    // Print reminders if they exist for each day
    for (int k = 0; k < November.month_days; k++) {
        if (November.reminders[k]) {
            printf("Day %2d:  %s\n", k + 1, November.reminder_str[k]);
        }
    }
}
