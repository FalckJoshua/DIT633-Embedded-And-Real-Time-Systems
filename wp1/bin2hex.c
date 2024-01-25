#include <stdio.h>   //Used for printf()
#include <stdlib.h>  //Used for strtol()
#include <string.h>  //Used for memcmp()

// Function declarations
int arg_is_binary(char *arg);  // If any argument is passed, check whether it is binary.
void bin2hex(char *bin);       // Print binary as hex.

/**
 * This program takes a binary number as an argument or pipeline and prints it as its hexadecimal representation.
 *
 * Work Packages 1: Exercise 4 - NUMBER-CONVERSION
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/
int main(int argc, char *argv[]) {
    if (argc > 1) {
        // Check if argument is "-h".
        if (strcmp(argv[1], "-h") == 0) {
            printf("Usage: ./bin2hex.exe <binary>\n");

            // End program.
            return 0;
        }

        // If there are arguments, check if they are binary.
        if (arg_is_binary(argv[1]) == 0) {
            printf("Error: Argument is not binary.\n");

            // End program.
            return 0;
        }

        // Pass argv[1] into function.
        bin2hex(argv[1]);

        // End program with success.
        return 0;

    }  // Else, read from stdin. See code below.

    char buffer[33];               // Buffer to hold the input. 32 bits + null terminator.
    char BOM[4] = "\xEF\xBB\xBF";  // UTF-8 BOM

    // Read from stdin until NULL.
    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        if (memcmp(buffer, BOM, 3) == 0) {  // For windows, ignore UTF-8 representation of BOM (Byte Order Mark)
            bin2hex(buffer + 3);            // If input starts with the BOM, increment the pointer by 3.
        } else {                            // Else:
            bin2hex(buffer);                // Just call the function with the full buffer.
        }
    }

    // End program with success.
    return 0;
}

// Function to check whether a passed argument is binary or not. Returns 1 if true, else 0 (false).
int arg_is_binary(char *arg) {             // Check if the argument is binary.
    while (*arg != '\0') {                 // While the argument is not null.
        if (*arg != '0' && *arg != '1') {  // If the argument is not 0 or 1.
            return 0;                      // Return 0 (false).
        }                                  //
        arg++;                             // Increment the pointer.
    }                                      //
    return 1;                              // Return 1 (true).
}

// Function to print binary as hexadecimal.
void bin2hex(char *bin) {
    // Convert binary to decimal
    long int decimal = strtol(bin, NULL, 2);

    // Convert decimal to hexadecimal and print
    printf("0x%lX\n", decimal);
}