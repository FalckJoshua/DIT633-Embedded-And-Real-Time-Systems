#include <ctype.h>   // Used for isdigit()
#include <stdio.h>   // Used for printf(), scanf()
#include <stdlib.h>  // Used for atoi(), malloc(), free()

// Enum to store the input values order for the input arguments / packing order
enum INPUT {
    ENGINE_ON,
    GEAR_POS,
    KEY_POS,
    BRAKE1,
    BREAK2
};

// Constants
const char* INPUT_NAMES[] = {"ENGINE_ON", "GEAR_POS", "KEY_POS", "BRAKE1", "BRAKE2"};  // Array to store the input names
const int MAX_RANGE[] = {1, 4, 2, 1, 1};                                               // Array to store the max range for each input
const int BIT_SIZE[] = {1, 3, 2, 1, 1};                                                // Array to store the bit size for each input

// Global variables
int input[5];  // Array to store the input values

// Function declarations
char* bit8_to_hex(int binary);

/**
 * This program takes 5 arguments, one for each enum 'INPUT' value, checking validity and then packing them into a single 8-bit value.
 * Afterwards, it prints the packed value in hexadecimal format.
 *
 * Work Packages 2: Exercise 4 - BITPACKING
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 2456372
 **/
int main(int argc, char* argv[]) {
    // Check if sufficient amount of arguments have been passed
    if (argc != 6) {
        printf("Invalid number of arguments, expected 5, got %d\n", argc - 1);
        return 1;  // Exit program
    }

    // Loop through all arguments and check if they are valid and assign them to the input array
    for (int i = 0; i < argc - 1; i++) {
        int arg_nr = i + 1;             // argv starts at 1, since 0 is the program name
        char* curr_arg = argv[arg_nr];  // Get the current argument

        // Check if the current argument is a number and greater than 0
        if (!isdigit(curr_arg[0])) {
            printf("Error: Argument %d is not a number\n", i);
            return 1;  // Exit program
        }

        // Convert the current argument to an integer
        int value = atoi(curr_arg);

        // Check if the current argument is within the valid range
        if (value < 0 || value > MAX_RANGE[i]) {
            printf("Error: Argument %d (for %s) is out of range, %d - %d, given: %s\n", arg_nr, INPUT_NAMES[i], 0, MAX_RANGE[i], curr_arg);
            return 1;  // Exit program
        }

        // Assign the current argument to the input array
        input[i] = value;
    }

    int packed = 0;                      // Variable to store the packed value
    for (int i = 0; i < 5; i++) {        // Loop through all the input values
        packed = packed << BIT_SIZE[i];  // Shift the packed value to the left by the bit size of the current input
        packed = packed | input[i];      // Add the current input value to the packed value
    }

    char* packed_hex = bit8_to_hex(packed);  // Convert the packed value to hexadecimal format
    printf("0x%s\n", packed_hex);            // Print the packed value in hexadecimal format'

    free(packed_hex);  // Free the memory allocated for the packed hexadecimal value

    return 0;  // Exit program
}

// Function to convert an 8-bit binary value to a hexadecimal string
char* bit8_to_hex(int binary) {
    char* hex = malloc(3 * sizeof(char));  // Allocate memory for 2 characters and a null terminator
    if (!hex) return NULL;                 // Check if memory allocation was successful

    char hex_values[] = "0123456789ABCDEF";

    for (int i = 1; i >= 0; i--) {             // Loop through the 2 characters in the hexadecimal value
        hex[i] = hex_values[binary & 0b1111];  // Get the last 4 bits of the binary value and convert it to a hexadecimal character
        binary = binary >> 4;                  // Shift the binary value to the right by 4 bits
    }

    hex[2] = '\0';  // Null-terminate the string

    return hex;  // Return the hexadecimal string
}
