#include <ctype.h>   // Used for isdigit()
#include <stdio.h>   // Used for printf(), scanf()
#include <stdlib.h>  // Used for atoi()
#include <string.h>  // Used for memset(), strcmp()

#define FILENAME "persons.bin"  // Name of the file to be created

// -----typedefs -------
typedef struct {
    char first_name[20];     // Max 19 characters + 1 for EOL
    char last_name[20];      // Max 19 characters + 1 for EOL
    char person_number[14];  // yyyy-mm-dd-nnnn   + 1 for EOL
} PERSON;

// Enum to hold possible operations depending on user input. Enum for better readability.
enum OPERATIONS {
    FIRST_OPTION,          // Used to check if input is valid, <= this value is invalid
    WRITE_NEW_FILE,        // 1. Creates a file and writes the first record
    APPEND_FILE,           // 2. Appends a new person to the file
    SEARCH_BY_FIRST_NAME,  // 3. Prints out the person if in list
    PRINT_FILE,            // 4. Prints out all persons in the file
    EXIT_PROGRAM,          // 5. Exit the program
    LAST_OPTION            // Used to check if input is valid, >= this value is invalid
};

// Function declarations
PERSON input_record(void);  // Reads in a person from the user
int file_exists();          // Checks if the file exists
// Menu functions
void write_new_file(PERSON *in_record);  // 1. Creates a file and writes the first record
void append_file(PERSON *in_record);     // 2. Appends a new person to the file
void search_by_first_name(char *name);   // 3. Prints out the person if in list
void print_file();                       // 4. Prints out all persons in the file

/**
 * This program writes and read 'PERSON' struct entries to a binary file. The user is able to do different operation depending on the input given while in the menu.
 *
 * Work Packages 2: Exercise 3 - BINARY FILES
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/
int main() {
    // Variable to store a person temporarily, read from input and passed as parameter to functions
    PERSON temp_person;

    // Variable to run main loop, set to 1 (true)
    int run = 1;

    // While run is 1 (true), run the loop
    while (run) {
        // Print possible operations
        printf("1. Create a new and delete the old file.\n");
        printf("2. Add a new person to the file.\n");
        printf("3. Search for a person in the file.\n");
        printf("4. Print out all in the file.\n");
        printf("5. Exit the program.\n");
        printf("Please enter a number between 1 and 5: ");

        // Read input from user, check if input is a number less than or equal to 'FIRST_OPTION' (0) and more than or equal to 'LAST_OPTION' (6), so, 1-5
        char input[255];     // Buffer variable to store input
        scanf("%s", input);  // Read input from user

        // While input is invalid, read input again.
        while (isdigit(*input) == 0 || atoi(input) <= FIRST_OPTION || atoi(input) >= LAST_OPTION) {
            // Print error message
            printf("Invalid input, please enter a number between 1 and 5: ");

            // Read input from user
            scanf("%s", input);
        }

        enum OPERATIONS input_value = atoi(input);  // Convert input to int and store in input_value, used for switch-case

        // Switch case for different operations depending on input
        switch (input_value) {
            case WRITE_NEW_FILE:  // If input is 'WRITE_NEW_FILE' (1), call write_new_file()
                temp_person = input_record();
                write_new_file(&temp_person);
                break;

            case APPEND_FILE:  // If input is 'APPEND_FILE' (2), call append_file()
                temp_person = input_record();
                append_file(&temp_person);
                break;

            case SEARCH_BY_FIRST_NAME:  // If input is 'SEARCH_BY_FIRST_NAME' (3), call search_by_first_name()
                printf("Enter first name to search for: ");
                char name[20];
                scanf("%19s", name);
                search_by_first_name(name);
                break;

            case PRINT_FILE:  // If input is 'PRINT_FILE' (4), call print_file()
                print_file();
                break;

            case EXIT_PROGRAM:  // If input is 'EXIT_PROGRAM' (5), set run to 0 (false), to end the loop.
                printf("Exiting program.");
                run = 0;  // End loop, set run to 0 (false)
                break;

            default:  // If input is not between 1 and 5, print error message
                printf("Invalid input.");
                break;
        }
        printf("\n");  // Newline for readability
    }

    return 0;  // Exit program, indicate success
}

// Function to read a person from the user
PERSON input_record() {
    PERSON person;                       // Create person struct
    memset(&person, 0, sizeof(person));  // Remove garbage from memory

    // Read input from user
    printf("Enter first name: ");
    scanf("%19s", person.first_name);
    printf("Enter last name: ");
    scanf("%19s", person.last_name);
    printf("Enter person number: ");
    scanf("%13s", person.person_number);

    // Return person read from user
    return person;
}

// Function to check if file exists
int file_exists() {
    FILE *file;                                   // Create file pointer
    if ((file = fopen(FILENAME, "r")) == NULL) {  // Open file for reading, if file does not exist, print error message and return 0 (false)
        printf("ERROR: File does not exist.\n");  //
        return 0;                                 // Return 0 (false)
    }                                             //
    fclose(file);                                 // Close file
    return 1;                                     // Return 1 (true)
}

// Function to print a person
void print_person(PERSON *person) {
    printf("First name: '%s', Last name: '%s', Person number: '%s'\n",
           person->first_name, person->last_name, person->person_number);
}

// Function to create a new file and initialize it with a person
void write_new_file(PERSON *in_record) {
    FILE *file;                                  // Create file pointer
    file = fopen(FILENAME, "wb");                // Open file for writing
    fwrite(in_record, sizeof(PERSON), 1, file);  // Write to file
    fclose(file);                                // Close file
}

// Function to append a person to a existing file
void append_file(PERSON *in_record) {
    if (!file_exists()) {  // Check if file exists
        return;            // If file does not exist, exit the function
    }

    FILE *file;                                  // Create file pointer
    file = fopen(FILENAME, "ab");                // Open file for appending
    fwrite(in_record, sizeof(PERSON), 1, file);  // Write to file
    fclose(file);                                // Close file
}

// Function to search for a person in the file
void search_by_first_name(char *name) {
    if (!file_exists()) {  // Check if file exists
        return;            // If file does not exist, exit the function
    }
    FILE *file;                                        // Create file pointer
    file = fopen(FILENAME, "rb");                      // Open file for reading
    PERSON person;                                     // Create person struct
    while (fread(&person, sizeof(PERSON), 1, file)) {  // Loop through the file for each person
        if (strcmp(person.first_name, name) == 0) {    // Compare first name with name
            print_person(&person);                     // Print person through method call
            fclose(file);                              // Close file
            return;                                    // Exit function
        }
    }
    printf("No person with that name was found.\n");
    fclose(file);  // Close file
}

// Function to print all persons in the file
void print_file() {
    if (!file_exists()) {  // Check if file exists
        return;            // If file does not exist, exit the function
    }
    FILE *file;                    // Create file pointer
    file = fopen(FILENAME, "rb");  // Open file for reading
    PERSON person;                 // Create person struct
    printf("---Printing file---\n");
    int counter = 1;                                   // initialize counter to 1
    while (fread(&person, sizeof(PERSON), 1, file)) {  // loop through the file and print each person
        printf("Person %d: ", counter);
        print_person(&person);  // Print person through method call
        counter++;              // Increment counter
    }
    printf("---End of file---\n");
    fclose(file);  // Close file
}
