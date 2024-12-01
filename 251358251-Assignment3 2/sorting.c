// Name of program : Sorting.c
// Author : Faozia Abedin - 251358251
// Purpose : This program allows users to input numbers, generate random ones, 
// and apply either Quick Sort or Bubble Sort to sort a 2D array while tracking the sorting duration.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> // For tolower function

// Function Prototypes
void handle_array(int arr[], int aux[], int start, int length, int operation);
void get_valid_input(int *n, int *m);
void sort_array(int arr[], int length, int algorithm);
void initialize_and_sort(int matrix[2][100], int n, int m, int is_new_input);
int partition(int arr[], int start, int end);
void quick_sort_recursive(int arr[], int low, int high);

int main() {
    int n, m;
    int matrix[2][100] = {0};  // Initialize matrix to zero
    char command;

    // Gather initial valid inputs for n and m
    get_valid_input(&n, &m);

    // Initialize and sort based on user input
    initialize_and_sort(matrix, n, m, 1);

    // Main loop for user interaction
    do {
        printf("\nEnter a command from the following list:\n");
        printf("(R) Re-generate random numbers and choose a different sorting algorithm\n");
        printf("(N) Enter another value for n and m, and enter new n numbers\n");
        printf("(S) Use a different sorting algorithm\n");
        printf("(Q) Quit\n");
        printf("Enter command: ");
        scanf(" %c", &command);
        command = tolower(command); // Convert command to lowercase for case-insensitive comparison

        // Switch to handle different user commands
        switch (command) {
            case 'r':
                // Re-generate random numbers for remaining slots, using existing `n` values
                initialize_and_sort(matrix, n, m, 0);
                break;
            case 'n':
                // Collect new values for n and m, reset the array, and sort
                get_valid_input(&n, &m);
                initialize_and_sort(matrix, n, m, 1);
                break;
            case 's':
                // Re-sort using the existing matrix values and prompt for new sorting method
                initialize_and_sort(matrix, n, m, 0);
                break;
            case 'q':
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid command.\n");
        }
    } while (command != 'q');

    return 0;
}

/*
 * get_valid_input: Prompts the user to enter values for n and m, ensuring they meet the criteria.
 * 
 * Parameters:
 *   - n: Pointer to the number of elements user will input
 *   - m: Pointer to the total size of the array
 */
void get_valid_input(int *n, int *m) {
    while (1) {
        printf("Enter the number of elements you would like to enter (n). n must be an even number: ");
        scanf("%d", n);

        // Check if n is even
        if (*n % 2 != 0) {
            continue;
        }

        // Inner loop for validating m
        while (1) {
            printf("Enter the length of the array (m). m must be an even number and >= n: ");
            scanf("%d", m);

            // Check if m is even and >= n
            if (*m % 2 != 0) {
                continue;
            }
            if (*m < *n) {
                continue;
            }

            // If m is valid, break the inner loop
            break;
        }

        // If both n and m are valid, break the outer loop
        break;
    }
}

/*
 * handle_array: Performs an operation on an array based on the operation type.
 * 
 * Parameters:
 *   - arr: The array to operate on
 *   - aux: An auxiliary array used for cloning if needed
 *   - start: Starting index (for filling random numbers or cloning)
 *   - length: Total size of the array
 *   - operation: Specifies the operation to perform:
 *       - 0: Fill array from 'start' index with random numbers
 *       - 1: Display the array
 *       - 2: Clone array elements from 'arr' to 'aux'
 */
void handle_array(int arr[], int aux[], int start, int length, int operation) {
    if (operation == 0) {  // Fill with random numbers from 'start' to 'length'
        for (int i = start; i < length; i++) {
            arr[i] = rand() % 10001;
        }
    } 
    else if (operation == 1) {  // Display array elements
        for (int i = 0; i < length; i++) {
            printf("%6d ", arr[i]);
        }
        printf("\n");
    } 
    else if (operation == 2) {  // Clone elements from 'arr' to 'aux'
        for (int i = 0; i < length; i++) {
            aux[i] = arr[i];
        }
    } 
    else {
        printf("Invalid operation specified.\n");
    }
}

/*
 * initialize_and_sort: Sets up the array, collects user input, fills remaining positions with random values,
 * and performs the chosen sorting algorithm.
 * 
 * Parameters:
 *   - matrix: 2D array to store original and sorted arrays
 *   - n: Number of elements to be input by user
 *   - m: Total size of the array
 *   - is_new_input: Flag to indicate if new input is required
 */
void initialize_and_sort(int matrix[2][100], int n, int m, int is_new_input) {
    int i = 0;

    // If new input is required, collect user input for the first row of the array
    if (is_new_input) {
        printf("Enter n elements: ");
        while (i < n) {
            if (scanf("%d", &matrix[0][i]) != 1) {
                printf("Invalid input detected. Filling remaining slots with random numbers.\n");
                break;
            }
            i++;
        }
        // Inform the user how many numbers were entered and how many will be randomly generated
        printf("You entered %d numbers, %d random numbers will be generated.\n", i, m - i);
        handle_array(matrix[0], NULL, i, m, 0);  // Fill remaining slots with random numbers
    } else {
        // For `R` command, keep existing values in the first `n` positions and re-generate random values for the remaining slots
        printf("You entered %d numbers, %d random numbers will be generated.\n", n, m - n);
        handle_array(matrix[0], NULL, n, m, 0);  // Fill remaining slots with random numbers starting from index `n`
    }

    // Choose sorting algorithm and sort
    int choice;
    printf("::Choose a sorting algorithm::\n|| (0)Quick sort || (1)Bubble sort ||\n");
    while (scanf("%d", &choice) != 1 || (choice != 0 && choice != 1)) {
        printf("Invalid choice, try again!\n");
        printf("::Choose a sorting algorithm::\n|| (0)Quick sort || (1)Bubble sort ||\n");
        while (getchar() != '\n'); // clear input buffer
    }
    
    // Clone the array to the second row for sorting
    handle_array(matrix[0], matrix[1], 0, m, 2);

    // Sort and time the sorting operation
    time_t start_time, end_time;
    time(&start_time);
    sort_array(matrix[1], m, choice);
    time(&end_time);

    // Display the original and sorted arrays, and the time taken
    printf("Raw array\n");
    handle_array(matrix[0], NULL, 0, m, 1);

    printf("Sorted array\n");
    handle_array(matrix[1], NULL, 0, m, 1);

    printf("Sorting duration (Sec): %ld\n", (end_time - start_time));
}



/*
 * sort_array: Sorts an array using either Quick Sort or Bubble Sort based on the chosen algorithm.
 * 
 * Parameters:
 *   - arr: The array to be sorted
 *   - length: Length of the array
 *   - algorithm: Sorting algorithm choice (0 for Quick Sort, 1 for Bubble Sort)
 */
void sort_array(int arr[], int length, int algorithm) {
    if (algorithm == 0) {
        quick_sort_recursive(arr, 0, length - 1);
    } 
    else if (algorithm == 1) {
        for (int pass = length - 1; pass > 0; pass--)
        for (int j = 0; j < pass; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

/*
 * quick_sort_recursive: A helper function to perform recursive Quick Sort.
 * 
 * Parameters:
 *   - arr: Array to be sorted
 *   - low: Starting index of the sort range
 *   - high: Ending index of the sort range
 */
void quick_sort_recursive(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort_recursive(arr, low, pi - 1);
        quick_sort_recursive(arr, pi + 1, high);
    }
}

/*
 * partition: Partitions the array for the Quick Sort algorithm, using the end element as a pivot.
 * 
 * Parameters:
 *   - arr: The array to be partitioned
 *   - start: Starting index of the partition
 *   - end: Ending index of the partition
 * 
 * Returns:
 *   The pivot index after partitioning
 */
int partition(int arr[], int start, int end) {
    int pivot = arr[end];
    int i = start - 1;

    for (int j = start; j < end; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[end];
    arr[end] = temp;

    return i + 1;
}
