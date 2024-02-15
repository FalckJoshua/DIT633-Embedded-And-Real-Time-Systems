#include <ctype.h>   // Used for atoi()
#include <stdio.h>   // Used for printf()
#include <stdlib.h>  // Used for malloc()
#include <string.h>  // Used for strcpy(), strlen()

// Function declarations
void copy_string(char* input, int free_mem);  // Function to copy the input string
char* copy_String_with_strcpy(char* string);  // Function to copy the input string with strcpy()
char* copy_String_with_loop(char* string);    // Function to copy the input string with a loop

/**
 * This program
 *
 * Work Packages 4: Exercise 6 - ARRAYS AND FILES
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/
int main(int argc, char* argv[]) {
    if (argc > 1) {                              // If there are command-line arguments:
        if (strlen(argv[1]) > 20) {              // Check if the input is too long
            printf("The input is too long.\n");  // Print an error message
            return 1;                            // Exit the program
        }

        copy_string(argv[1], 0);  // Call the copy_string function with the input string and free_mem = 0 (input is not dynamically allocated)

    }

    else {  // Else, if there are no command-line arguments:

        char* input = (char*)malloc(20 * sizeof(char));  // Allocate memory for the input string

        if (fgets(input, 20, stdin) == NULL) {  // Read input from stdin, allows to use "< myfile.txt" to read from file

            printf("Error reading input.\n");  // Print the error message
            free(input);                       // Free the memory of the input string
            return 1;                          // Return 1 to indicate an error
        }

        copy_string(input, 1);  // Call the copy_string function with the input string and free_mem = 1 (input is dynamically allocated)
    }

    return 0;  // Return 0 to indicate successful execution
}

// Function to copy the input string manually
void copy_string(char* input, int free_mem) {
    printf("Input: %s\n", input);

    char* first_copy;   // Declare a pointer to the first copy
    char* second_copy;  // Declare a pointer to the second copy

    first_copy = copy_String_with_strcpy(input);  // Assign first_copy to the result of the copy_String_with_strcpy function
    if (first_copy == NULL) {
        printf("Error allocating memory for copy.\n");  // Print an error message
    } else {
        printf("Copy with strcpy: %s\n", first_copy);  // Print the first copy
    }

    second_copy = copy_String_with_loop(input);  // Assign second_copy to the result of the copy_String_with_loop function
    if (second_copy == NULL) {
        printf("Error allocating memory for copy.\n");  // Print an error message
    } else {
        printf("Copy with loop: %s\n", second_copy);  // Print the second copy
    }

    if (free_mem) {   // If the function was called with free_mem = 1 (input is dynamically allocated):
        free(input);  // Free the memory of the input string
    }
    free(first_copy);   // Free the memory of the first copy
    free(second_copy);  // Free the memory of the second copy
}

// Function to copy the input string with strcpy()
char* copy_String_with_strcpy(char* string) {
    char* copy = (char*)malloc((strlen(string) + 1) * sizeof(char));  // Allocate memory for the copy
    if (copy == NULL) {                                               // If the memory allocation failed:
        return NULL;                                                  // Return NULL, indicating an error
    }

    strcpy(copy, string);  // Copy the input string to the copy

    return copy;  // Return the copy
}

char* copy_String_with_loop(char* string) {
    char* copy = (char*)malloc((strlen(string) + 1) * sizeof(char));  // Allocate memory for the copy
    if (copy == NULL) {                                               // If the memory allocation failed:
        return NULL;                                                  // Return NULL, indicating an error
    }

    int i;                                  // Declare a variable to use as a counter
    for (i = 0; i < strlen(string); i++) {  // Loop through the input string
        copy[i] = string[i];                // Copy each character to the copy
    }                                       //
    copy[i] = '\0';                         // Add the null terminator to the end of the copy

    return copy;  // Return the copy
}