/* interact.h
   Faozia Abedin
   251358251
*/
#ifndef INTERACT_H
#define INTERACT_H

#include "reminder.h"

// Function to interact with the user for reading reminders
int readReminder(char *reminder, int maxLen, struct Month *month);

// Flushes the input buffer to handle invalid inputs
void flushBuffer();

// Reads reminders from the file and populates the month structure
void readFromFile(struct Month *month);

// Writes reminders to the file before exiting
void writeToFile(struct Month *month);

#endif
