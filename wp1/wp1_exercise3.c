#include <stdio.h>   //Used for printf(), scanf()
#include <stdlib.h>  //Used for srand(), rand(), atoi()
#include <time.h>    //Used for time(), to seed srand()

// Global variables
int ACTUAL_NUMBER;      // Initialize ACTUAL_NUMBER
int GUESSED_NUMBER;     // Initialize GUESSED_NUMBER
int GUESS_COUNTER = 1;  // Initialize & declare GUESS_COUNTER
int MAX_GUESSES = 10;   // Initialize & declare MAX_GUESSES
int ACTIVE_GAME = 1;    // Initialize & declare ACTIVE_GAME

// Function prototypes
int charIsNumber(char *input);

/**
 * This program is a simple game where a random number is generated, and the user is prompted to guess it.
 * The game ends when the user guesses the number or when they exceed the maximum number of allowed guesses.
 *
 * Work Packages 1: Exercise 3 - GUESS THE NUMBER GAME
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 315775
 **/
int main(int argc, char *argv[]) {
    srand(time(0));                      // Initialize random number generator.
    ACTUAL_NUMBER = (rand() % 100) + 1;  // Generate a random number between 1 and 100

    printf("Give us your best guess!\n");  // Print message
    char input[100];                       // Declare input variable

    while (ACTUAL_NUMBER != GUESSED_NUMBER) {  // Loop until user guesses the number
        scanf("%s", input);                    // Get user input

        if (charIsNumber(input) == 0) {          // Check if the provided input is a number
            printf("Please enter a number!\n");  // Print message
            continue;                            // Skip the rest of this iteration of the loop (i.e restart)
        }

        GUESSED_NUMBER = atoi(input);  // Convert input to int

        if (GUESSED_NUMBER < 1 || GUESSED_NUMBER > 100) {          // Check if the provided input is between 1 and 100
            printf("Please enter a number between 1 and 100!\n");  // Print message
            continue;                                              // Skip the rest of this iteration of the loop (i.e restart)
        }

        if (GUESSED_NUMBER > ACTUAL_NUMBER) {                                 // Check if guessed number is lower than the actual number
            printf("Number is lower! You got it next time :)\n");             // Print message
            printf("-- %d guesses left! --\n", MAX_GUESSES - GUESS_COUNTER);  // Print amount of guesses left
            GUESS_COUNTER++;                                                  // Increment guess counter
        }

        else if (GUESSED_NUMBER < ACTUAL_NUMBER) {                            // Check if guessed number is higher than the actual number
            printf("Number is higher! Next time you'll get it :)\n");         // Print message
            printf("-- %d guesses left! --\n", MAX_GUESSES - GUESS_COUNTER);  // Print amount of guesses left
            GUESS_COUNTER++;                                                  // Increment guess counter
        }

        else if (GUESSED_NUMBER == ACTUAL_NUMBER) {  // Check if guessed number is the actual number
            printf("You guessed correctly! :)\n");   // Print message
            ACTIVE_GAME = 0;                         // Set ACTIVE_GAME to 0 to end the game
        }

        if (GUESS_COUNTER > MAX_GUESSES) {                 // Check if user has exceeded the maximum number of guesses
            printf("You ran out of guesses! :(\n");        // Print message
            printf("The number was %d\n", ACTUAL_NUMBER);  // Print the actual number
            ACTIVE_GAME = 0;                               // Set ACTIVE_GAME to 0 to end the game
        }

        if (ACTIVE_GAME == 0) {                             // Check if ACTIVE_GAME is 0 (i.e game is over)
            printf("Would you like to play again Y/N \n");  // Print message
            char answer;                                    // Initialize variable to store user answer
            scanf(" %c", &answer);                          // Get user input
            if (answer == 'Y') {                            // Check if user answers Y
                ACTIVE_GAME = 1;                            // Set ACTIVE_GAME to 1 to start a new game
                GUESS_COUNTER = 1;                          // Reset GUESS_COUNTER
                ACTUAL_NUMBER = (rand() % 100) + 1;         // Generate a random number between 1 and 100
                printf("Give us your best guess!\n");       // Print message
                continue;                                   // Skip the rest of this iteration of the loop (i.e restart)
            } else {
                break;  // If user doesn't answer Y end the game (break the while loop)
            }
        }
    }

    return 0;  // Return 0 (success)
}

// Function to check if char array (input, the given argument) is a number
// Returns 1 (true) if input is a number, else, 0 (false)
int charIsNumber(char *input) {
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
