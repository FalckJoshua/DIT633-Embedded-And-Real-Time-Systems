#include <stdio.h>   //Used for printf()
#include <stdlib.h>  //Used for atoi()

// Function declarations
int charIsNumber(char *input);
void dec2bin(unsigned int dec);

// Define bit sizes, all unsigned
#define bit8decimal 255          // 2^8 - 1
#define bit16decimal 65535       // 2^16 - 1
#define bit24decimal 16777215    // 2^24 - 1
#define bit32decimal 4294967295  // 2^32 - 1

// Define typedef bytes for different bit sizes
typedef unsigned long int bit32;  // 32-bit

/**
 * This program takes a decimal number as an argument and prints it as its binary representation.
 *
 * Work Packages 1: Exercise 4 - NUMBER-CONVERSION
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/
int main(int argc, char *argv[]) {
    // Check if an argument has been provided
    if (argc != 2) {
        printf("ERROR: Invalid number of arguments. Use '-h' for help.\n");
        return 0;
    }

    // Check if argument is a number
    if (charIsNumber(argv[1]) == 0) {
        printf("ERROR: Argument is not a number. Use '-h' for help.\n");
        return 0;
    }

    // argv[1] is the first argument, if it is "-h", print help
    // argv[1][0] is the first character in the first argument, i.e '-'
    // argv[1][1] is the second character in the first argument, i.e 'h'
    if (argv[1][0] == '-' && argv[1][1] == 'h') {
        printf("Provide a decimal number in the argument and it will be converted to its binary form. (Maximum 2^32-1)\n");
        return 0;
    }

    // Call dec2bin function to print decimal argument as its binary representation.
    dec2bin(atoi(argv[1]));

    // End program with success.
    return 0;
}

// Function to check if char array (input, the given argument) is a number
// Returns 1 (true) if input is a number, else, 0 (false)
int charIsNumber(char *input) {
    while (*input != '\0') {                 // Loop through each character in the char array (input)
        if (*input < '0' || *input > '9') {  // Check if character is a number
            return 0;                        // Return 0 (false)
        }                                    //
        input++;                             // Increment loop (pointer to next address)
    }                                        //
    return 1;                                // Return 1 (true)
}

// Function to convert decimal to binary
void dec2bin(unsigned int dec) {
    int shifts = 0;  // Variable to store amount of shifts

    // 1 byte case
    if (dec <= bit8decimal) {
        shifts = 7;  // Set amount of shifts to 7 (1 byte = 8 bits, 8-1=7).
    }

    // 2 byte case
    else if (dec <= bit16decimal) {
        shifts = 15;  // Set amount of shifts to 15 (2 bytes = 16 bits, 16-1=15).
    }

    // 3 byte case
    else if (dec <= bit24decimal) {
        shifts = 23;  // Set amount of shifts to 23 (3 bytes = 24 bits, 24-1=23).
    }

    // 4 byte case
    else if (dec <= bit32decimal) {
        shifts = 31;  // Set amount of shifts to 31 (4 bytes = 32 bits, 32-1=31).
    }

    //  Error case
    else {
        printf("ERROR: Number is too large. Use '-h' for help.\n");
        return;  // Exit function
    }

    bit32 mask = 0b1;       // Create bit mask.
    mask = mask << shifts;  // Shift mask to the left by the amount of shifts (Depending on which byte case).

    // Loop through each bit in the mask
    for (size_t i = 0; i <= shifts; i++) {
        if (dec & mask) {  // Check if current bit of dec is 1
            printf("1");   // Print 1
        } else {           // Else, current bit of dec is 0
            printf("0");   // Print 0
        }                  //
        mask = mask >> 1;  // Increment mask to the right by 1
    }
    printf("\n");  // Print new line to showcase end of piped output. Used for bin2hex.c (dec2bin.exe <decimal> | bin2hec.exe).
}
