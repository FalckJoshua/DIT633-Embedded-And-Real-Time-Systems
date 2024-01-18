#include <stdio.h>   // Used for printf()
#include <stdlib.h>  // Used for atoi()

// Global variables
int SHIFTS;  // Number of shifts to encrypt the input with, given as an command line argument

// Function prototypes
int charIsNumber(char* input);  // Returns 1 if input is a number, 0 otherwise
void encrypt(char* input);      // Encrypts (each char shifted with 'SHIFTS') the inputted char array and prints it

int main(int argc, char* argv[]) {
    // Check if an argument has been proviided
    if (argc != 2) {
        printf("Please provide a number as an argument\n");
        return 0;  // End program
    }

    // Check if provided argument is a number (0 = false, 1 = true)
    if (charIsNumber(argv[1]) == 0) {
        printf("Please provide a number as an argument\n");
        return 0;  // End program
    }

    // Set variable for number of shifts
    SHIFTS = atoi(argv[1]);

    // Get input from user
    printf("Please enter text:\n");      // Print message
    char input[100];                     // Create variable (char array) to store input
    while (scanf("%s", input) != EOF) {  // Loop until user inputs EOF
        encrypt(input);                  // Call encrypt() method on input
        printf("\n");                    // Print new line
    }

    // Return 0 (no errors)
    return 0;
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

// Function to encrypt (shift each le)ter by 'SHIFTS
void encrypt(char* input) {
    // Loop through each character in the char array (input)
    while (*input != '\0') {

        // Store current character in variable
        char current_char = *input;

        // Check if letter is uppercase
        if (current_char >= 'A' && current_char <= 'Z') {
            // Alphabet in ASCII starts at 65 (A) and ends at 90 (Z),
            // the '%' (modulo) operator is used to convert the input into a range of 0 - 25 (26 letters),
            // aftewards 65 is added back to get the correct number represenation of the uppercase letter in ASCII.
            current_char = (current_char - 65 + SHIFTS) % 26 + 65;
            printf("%c", current_char);
        }

        // Check if letter is lowercase
        else if (current_char >= 'a' && current_char <= 'z') {
            // Alphabet in ASCII starts at 97 (a) and ends at 122 (z),
            // the '%' (modulo) operator is used to convert the input into a range of 0 - 25 (26 letters),
            // aftewards 97 is added back to get the correct number represenation of the lowercase letter in ASCII.
            current_char = (current_char - 97 + SHIFTS) % 26 + 97;
            printf("%c", current_char);
        }

        // Increment loop (pointer to next address)
        input++;
    }
}
