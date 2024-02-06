// Includes
#include <stdio.h>   // Used for printf(), scanf()
#include <stdlib.h>  // Used for malloc(), free()
#include <time.h>    // Used for srand(), time(), rand()

// Constants
#define AMOUNT 5            // Amount of nodes in the list
#define MAX 100             // Max value of a node
#define ADD_FIRST_VALUE 42  // Value to add to the start of the list

// Struct to hold a node for a linked list
typedef struct q {
    int number;
    struct q* next;
    struct q* prev;
} REGTYPE;

// Function declarations
REGTYPE* random_list();
REGTYPE* add_first(REGTYPE* old_head, int data);
void print_list(REGTYPE* head);

/**
 * This program creates a linked list filled with random numbers. Then it prints the current list. Then it appends a new first node to the list and prints the new list.
 *
 * Work Packages 2: Exercise 2 - LINKED LIST
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/
int main(int argc, char* argv[]) {
    // Initialize variables
    REGTYPE *act_post, *head = NULL;

    srand(time(0));        // Random seed
    head = random_list();  // Call function to create a linked list of random numbers
    print_list(head);      // Call function to print the list

    printf("\nExtending list:\n");
    head = add_first(head, ADD_FIRST_VALUE);  // Call function to add a new node to the start of the list
    print_list(head);            // Call function to print the list

    // Loop to free all nodes (free up memory)
    while ((act_post = head) != NULL) {
        head = act_post->next;  // Move head to next node
        free(act_post);         // Free current node
    }

    return 0;  // Exit program
}

// Function to create a linked list of random numbers
REGTYPE* random_list() {
    // Initialize variables
    REGTYPE *top, *old, *item;

    // Create first node
    top = (REGTYPE*)malloc(sizeof(REGTYPE));  // Create new node

    // Assign values to first node
    top->number = rand() % MAX;
    top->prev = NULL;
    top->next = NULL;

    // Set old to first node
    old = top;

    // Loop to create rest of the nodes
    for (int i = 1; i < AMOUNT; i++) {             // Create AMOUNT-1 new nodes and add to list (head is already created)
        item = (REGTYPE*)malloc(sizeof(REGTYPE));  // Create new node
        // Assign values to new node
        item->number = rand() % MAX;
        item->prev = old;
        item->next = NULL;

        // Set old->next to new node
        old->next = item;

        // Set old to new node
        old = item;
    }

    return (top);
}

// Function to append a new node to the start of a linked list
REGTYPE* add_first(REGTYPE* old_head, int data) {
    // Initialize new_head
    REGTYPE* new_head = (REGTYPE*)malloc(sizeof(REGTYPE));

    // Assign values to new_head
    new_head->number = data;
    new_head->prev = NULL;
    new_head->next = old_head;

    // Set old_head->prev to new_head
    old_head->prev = new_head;

    // Return new_head, which is now the first element of the list
    return new_head;
}

// Function to print a linked list
void print_list(REGTYPE* head) {
    REGTYPE* current = head;              // Variable used to loop through the list
    while (current != NULL) {             // Loop until current is NULL (end of list)
        printf("%d\n", current->number);  // Print
        current = current->next;          // Move to next node
    }
}
