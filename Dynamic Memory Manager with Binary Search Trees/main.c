/* main.c
   Faozia Abedin
   251358251
*/

#include "interact.h"
#include "reminder.h"
#include "linked_list.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// Global pointer to the current month for signal handling
struct Month *globalMonth = NULL;

// Handles SIGINT (CTRL+C) and SIGTERM (kill)
// Saves reminders to the file before exiting
void handleInterrupt(int sig) {
    if (globalMonth) {
        printf("\nProgram interrupted...\nWriting to file...\n");
        writeToFile(globalMonth); // Save reminders
    }
    exit(0); // Graceful exit
}

// Handles SIGSEGV (Segmentation Fault)
// Attempts to save reminders before exiting due to an error
void handleSegmentationFault(int sig) {
    fprintf(stderr, "\nSegmentation fault occurred.");
    if (globalMonth) {
        printf("Attempting to save reminders before exiting...\n");
        writeToFile(globalMonth); // Save reminders
    }
    exit(1); // Exit with error
}

int main() {
    struct Month currentMonth;
    globalMonth = &currentMonth; // Set global pointer to the current month

    // Register signal handlers
    signal(SIGINT, handleInterrupt);         // Handle CTRL+C interrupt
    signal(SIGTERM, handleInterrupt);        // Handle termination signal
    signal(SIGSEGV, handleSegmentationFault); // Handle segmentation fault

    // Initialize the month with default values
    initializeMonth(&currentMonth);

    // Load reminders from the file into the calendar
    readFromFile(&currentMonth);

    char input[MAX_STR_LEN];    // Buffer to read input from the user
    char reminder[MAX_STR_LEN]; // Buffer to store the reminder text
    int day;                    // Variable to store the entered day

    while (1) { // Infinite loop to read user input
        printf("Enter day and reminder (0 to quit): ");

        // Read a full line of input
        if (!fgets(input, sizeof(input), stdin)) {
            printf("Error reading input. Please try again.\n");
            continue; // Retry if input fails
        }

        // Parse the input into a day and a reminder
        if (sscanf(input, "%d %[^\n]", &day, reminder) < 1) {
            printf("Invalid input. Please enter a valid day between 1 and %d (or 0 to quit).\n", currentMonth.month_days);
            continue; // Retry if parsing fails
        }

        // Exit condition
        if (day == 0) {
            break;
        }

        // Check for invalid day ranges
        if (day < 1 || day > currentMonth.month_days) {
            printf("Invalid day. Please enter a day between 1 and %d.\n", currentMonth.month_days);
            continue; // Retry if day is out of range
        }

        // Add the reminder to the linked list for the given day
        currentMonth.reminders[day - 1] = addNode(currentMonth.reminders[day - 1], reminder);

        // Display the updated calendar with reminders
        printCalendar(&currentMonth);
    }

    // Save reminders to the file before exiting
    writeToFile(&currentMonth);

    // Free all allocated memory for reminders
    for (int i = 0; i < currentMonth.month_days; i++) {
        freeAll(currentMonth.reminders[i]);
    }

    return 0; // Program ends successfully
}
