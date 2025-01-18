/* interact.c
   Faozia Abedin
   251358251
*/
#include "interact.h"
#include "linked_list.h"
#include "reminder.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "reminders.txt" // Name of the file used to store reminders


int readReminder(char *reminder, int maxLen, struct Month *month) {
    int day;
    printf("____________________________________\n");
    printf("Enter day and reminder (0 to quit): ");
    scanf("%d", &day);
    getchar(); // Consume the newline character left in the input buffer

    // Validates the entered day
    if (day < 0 || day > month->month_days) { 
        printf("Invalid day. Please enter a valid day between 1 and %d (or 0 to quit).\n", month->month_days);
        return -1; // Indicate invalid input
    }
    if (day == 0) { 
        return 0; // Exit condition
    }

    // Reads the reminder string and removes the trailing newline character
    fgets(reminder, maxLen, stdin);
    reminder[strcspn(reminder, "\n")] = '\0'; // Remove the newline from the input

    return day; // Return the valid day
}

// Clears the input buffer to handle invalid or extra inputs
void flushBuffer() {
    while (getchar() != '\n') {
        // Read and discard characters until a newline is encountered
    }
}

// Reads reminders from the file and populates the month structure
// - month: Pointer to the current month structure
void readFromFile(struct Month *month) {
    FILE *file = fopen(FILENAME, "r"); // Open the file for reading
    if (!file) return; // If the file does not exist, do nothing

    int day; // Variable to store the day read from the file
    char reminder[MAX_STR_LEN]; // Buffer to store the reminder read from the file

    // Read day and reminder pairs from the file
    while (fscanf(file, "%d %[^\n]", &day, reminder) == 2) {
        // Only add the reminder if the day is valid
        if (day > 0 && day <= month->month_days) {
            month->reminders[day - 1] = addNode(month->reminders[day - 1], reminder);
        }
    }
    fclose(file); // Close the file after reading
}

// Writes all reminders from the month structure to the file
// - month: Pointer to the current month structure
void writeToFile(struct Month *month) {
    FILE *file = fopen(FILENAME, "w"); // Open the file for writing
    if (!file) {
        perror("Error opening file"); // Print an error message if the file cannot be opened
        return;
    }

    // Iterate through all the days in the month
    for (int i = 0; i < month->month_days; i++) {
        struct Node *current = month->reminders[i]; // Pointer to the list of reminders for the day

        // Write each reminder for the day to the file
        while (current != NULL) {
            fprintf(file, "%d %s\n", i + 1, current->reminder); // Write day and reminder to the file
            current = current->next; // Move to the next reminder
        }
    }
    fclose(file); // Close the file after writing
}
