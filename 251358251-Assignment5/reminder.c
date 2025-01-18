/* reminder.c
   Faozia Abedin
   251358251
*/

#include "reminder.h"
#include "linked_list.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initializeMonth(struct Month *month) {
    time_t now = time(NULL);           // Get the current time
    struct tm *t = localtime(&now);   // Convert to local time

    month->month_idx = t->tm_mon;     // Set the current month index (0 = Jan, 11 = Dec)

    t->tm_mday = 1;                   // Set day to the 1st of the current month
    mktime(t);                        // Normalize the time structure
    month->start_day = t->tm_wday;    // Get the starting weekday of the month

    // Determine the number of days in the current month
    month->month_days = 1;
    while (t->tm_mon == month->month_idx) {
        month->month_days = t->tm_mday; // Update the day count
        t->tm_mday++;                  // Move to the next day
        mktime(t);                     // Normalize the time structure
    }

    for (int i = 0; i < month->month_days; i++) {
        month->reminders[i] = NULL;   // Clear all reminders
    }
}

void printCalendar(struct Month *month) {
    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    const char *weekdays[] = {
        "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
    };

    printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");

    for (int j = 0; j < month->start_day; j++) {
        printf("     "); // Print leading spaces for the first row
    }

    for (int i = 1; i <= month->month_days; i++) {
        if (month->reminders[i - 1]) {
            printf("(%2d) ", i); // Highlight days with reminders
        } else {
            printf(" %2d  ", i); // Print regular days
        }

        if ((i + month->start_day) % 7 == 0) { // Start a new row after Saturday
            printf("\n");
        }
    }
    printf("\n\n%s reminders:\n", months[month->month_idx]); // Print the month's name

    for (int i = 0; i < month->month_days; i++) {
        if (month->reminders[i]) {
            int weekdayIndex = (month->start_day + i) % 7; // Calculate the weekday
            printf("%s %2d:: ", weekdays[weekdayIndex], i + 1); // Print weekday and day
            printList(month->reminders[i]); // Print reminders for the day
        }
    }
}
