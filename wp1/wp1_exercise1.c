#include <stdio.h>   //Used for printf()
#include <stdlib.h>  //Used for atoi()

// Function declaration
int charIsNumber(char* input);  // Check if the given input is a number

// Define sentence for input 1
#define first "Hello\n"

// Define sentence for input 2
#define second "World\n"

// Define sentence for input 3
#define third "!\n"

// Define sentence for input 4
#define fourth "Hello World!\n"

// Define sentence for input 5
#define fifth "Hello World! (again)\n"

// Define sentence for wrong input
#define inputError "Error, input must be a number between 1-5 \n"

/**
 * This program waits for user input, should be between 1 - 5, and prints a unique sentence depending on the number.
 *
 * Work Packages 1: Exercise 1 - IF-STATEMENTS
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 315775
 **/
int main(int argc, char* argv[]) {
    char input[255];                              // Declare input variable
    while (1 == 1) {                              // Keep looping while input is between 1 - 5
        printf("Enter a number between 1-5 \n");  // Print
        scanf("%s", input);                       // Scan for input

        if (charIsNumber(input) == 0) {  // Check if the provided input is a number
            printf("%s", inputError);    // Print error message
            return 0;
        }

        int number = atoi(input);  // Convert input to int

        // If  statements
        switch (number) {
            case 1:                        // If == 1
                printf("%s", first);       // Print first
                break;                     // Break -> exit switch / if statement
            case 2:                        // If == 2
                printf("%s", second);      // Print second
                break;                     // Break -> exit switch / if statement
            case 3:                        // If == 3
                printf("%s", third);       // Print third
                break;                     // Break -> exit switch / if statement
            case 4:                        // If == 4
                printf("%s", fourth);      // Print fourth
                break;                     // Break -> exit switch / if statement
            case 5:                        // If == 5
                printf("%s", fifth);       // Print fifth
                break;                     // Break -> exit switch / if statement
            default:                       // Else, exit and return
                printf("%s", inputError);  // Print error message
                return 0;                  // Return success
        }
    }
}

// Function to check if char array (input, the given argument) is a number
// Returns 1 (true) if input is a number, else, 0 (false)
int charIsNumber(char* input) {
    // Loop through each character in the char array (input)
    while (*input != '\0') {
        // Check if character is a number
        if (*input < '0' || *input > '9') {
            return 0;  // Return 0 (false)
        }
        input++;  // Increment loop (pointer to next address)
    }
    return 1;  // Return 1 (true)
}
