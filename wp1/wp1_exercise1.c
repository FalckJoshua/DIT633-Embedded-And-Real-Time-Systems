#include <stdio.h>  //Used for printf()

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
#define inputError "Error, number must be between 1-5 \n"

/**
 * This program waits for user input, should be between 1 - 5, and prints a unique sentence depending on the number.
 *
 * Work Packages 1: Exercise 1 - IF-STATEMENTS
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/
int main(int argc, char *argv[]) {
    int input = 0;                                // Declare input variable
    while (input > 1 || input < 5) {              // Keep looping while input is between 1 - 5
        printf("Enter a number between 1-5 \n");  // Print
        scanf("%d", &input);                      // Scan for input

        // If  statements
        switch (input) {
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
                printf("%s", inputError);  // Print error message
            default:                       // Else, exit and return
                return 0;                  // Return success
        }
    }
}
