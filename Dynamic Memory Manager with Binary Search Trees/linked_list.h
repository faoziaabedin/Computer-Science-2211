/* linked_list.h
   Faozia Abedin
   251358251
*/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "reminder.h"

// Adds a new reminder to the linked list
struct Node *addNode(struct Node *head, const char *reminder);

// Deletes a specific reminder from the linked list
struct Node *deleteNode(struct Node *head, int index);

// Frees all nodes in the linked list
void freeAll(struct Node *head);

// Prints the reminders in the linked list
void printList(struct Node *head);

#endif
