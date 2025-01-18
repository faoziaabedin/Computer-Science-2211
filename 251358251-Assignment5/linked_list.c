/* linked_list.c
   Faozia Abedin
   251358251
*/
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Adds a new node containing the given reminder to the linked list
struct Node *addNode(struct Node *head, const char *reminder) {
    struct Node *newNode = malloc(sizeof(struct Node)); // Allocate memory for a new node
    if (!newNode) {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    strncpy(newNode->reminder, reminder, MAX_STR_LEN); // Copy the reminder into the node
    newNode->next = head; // Link the new node to the head of the list
    return newNode; // Return the updated head
}

// Deletes the node at the given index (1-based) from the linked list
struct Node *deleteNode(struct Node *head, int index) {
    if (!head || index < 1) return head; // Do nothing if the list is empty or index is invalid

    struct Node *current = head;
    struct Node *previous = NULL;

    // Traverse to the specified node
    for (int i = 1; i < index && current; i++) {
        previous = current;
        current = current->next;
    }

    if (current) { // If the node to delete is found
        if (previous) {
            previous->next = current->next; // Remove the node from the list
        } else {
            head = current->next; // Update the head if the first node is removed
        }
        free(current); // Free the memory of the removed node
    }

    return head; // Return the updated list
}

// Frees all nodes in the linked list
void freeAll(struct Node *head) {
    struct Node *current = head;

    while (current) {
        struct Node *temp = current; // Keep track of the current node
        current = current->next; // Move to the next node
        free(temp); // Free the current node
    }
}

// Prints all reminders in the linked list with their indices
void printList(struct Node *head) {
    struct Node *current = head;
    int count = 1;

    while (current) { // Iterate through the list
        printf("(%d) %s\n", count++, current->reminder); // Print the index and reminder
        current = current->next; // Move to the next node
    }
}
