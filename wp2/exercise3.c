#include <stdio.h>
#include <stdlib.h>

// -----typedefs -------
typedef struct {
    char first_name[20];
    char fam_name[20];
    char pers_number[13];  // yyyymmddnnnc
} PERSON;

// Function declaration (to be extend)
PERSON input_record(void);               // Reads a person’s record.
void write_new_file(PERSON *in_record);  // Creates a file and
// writes the first record
void printfile(void);                  // Prints out all persons in the file
void search_by_firstname(char *name);  // Prints out the person if
// in list
void append_file(PERSON *in_record);  // appends a new person to the file

/**
 * This program creates a linked list filled with random numbers. Then it prints the current list. Then it appends a new first node to the list and prints the new list.
 *
 * Work Packages 2: Exercise 3 - BINARY FILES
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/
int main(void) {
    PERSON ppost;
    return (0);
}

void printMenu() {
    printf("1 Create a new and delete the old file.\n");
    printf("2 Add a new person to the file.\n");
    printf("3 Search for a person in the file.\n");
    printf("4 Print out all in the file.\n");
    printf("5 Exit the program.");
}

void commanderBOSS() {
    int input;
    do {
        printMenu();
        scanf("%d", input);
        switch (input) {
            case 1:
                write_new_file();
                break;
            case 2:
                append_file();
                break;
            case 3:
                search_by_firstname();
                break;
            case 4:
                printfile();
                break;
            case 5:
                printf("Exiting program.");
                break;
            default:
                printf("Invalid input.");
                break;
        }
    } while (input != 5);
}