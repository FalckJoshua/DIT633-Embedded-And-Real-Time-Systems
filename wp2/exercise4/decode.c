#include <ctype.h>   // Used for isdigit(), isxdigit()
#include <stdio.h>   // Used for printf(), scanf()
#include <stdlib.h>  // Used for atoi(), malloc(), free()
#include <string.h>  // Used for strlen()

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

// Function declarations
void decode(int packed);

/**
 * This program takes 1 argument, a hex value, and decodes it into the 5 input values, checking validity and then printing them.
 *
 * Work Packages 2: Exercise 4 - BITPACKING
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 2456372
 **/
int main(int argc, char* argv[]) {
    if (argc != 2) {  // Check if the number of arguments is not 2
        printf("Error: Invalid number of arguments, expected 1, got %d\n", argc - 1);
        return 1;  // Exit program
    }

    int length = strlen(argv[1]);  // Get the length of the provided argument
    if (length != 2) {             // Check to see if the provided argument is more than 2 characters
        printf("Error: Too many characters, expected 2, got: %d\n", length);
        return 1;  // Exit program
    }

    for (int i = 0; i < 2; i++) {     // Loop through all the characters in the provided argument
        if (!isxdigit(argv[1][i])) {  // Check if the character is not a valid hex number
            printf("Error: Argument is not a valid hex number\n");
            return 1;  // Exit program
        }
    }

    int packed;                      // Variable to store the packed value
    sscanf(argv[1], "%x", &packed);  // Convert the hex value to an integer

    decode(packed);  // Call function to decode the binary value. If valid 'packed', print the value of each enum 'INPUT' value

    return 0;  // Exit program, indicate success
}

void decode(int packed) {
    int unpacked[5];                                      // Array to store the the binary values separately for each input, in the order of the enum INPUT
    for (int i = 4; i >= 0; i--) {                        // Loop through all the input values, in reverse order
        unpacked[i] = packed & ((1 << BIT_SIZE[i]) - 1);  // Mask the packed value with the bit size
        packed = packed >> BIT_SIZE[i];                   // Shift the packed value to the right by the bit size
    }

    for (int i = 0; i < 5; i++) {          // Loop through all the input values
        if (unpacked[i] > MAX_RANGE[i]) {  // Check if the unpacked value is out of range
            printf("Error: Unpacked value for %s is out of range (%d - %d), got: %d\n", INPUT_NAMES[i], 0, MAX_RANGE[i], unpacked[i]);
            return;  // Exit function
        }
    }

    // Print the unpacked values
    printf(" ___________________\n");                           // Make adorable box
    printf("|Name          Value|\n");                          // ----||----
    printf("|-------------------|\n");                          // ----||----
    for (int i = 0; i < 5; i++) {                               // Loop through all the input values
        printf("|%-15s %-3d|\n", INPUT_NAMES[i], unpacked[i]);  // print the input name and value
    }                                                           //
    printf("|___________________|\n");                          // Close the cool box
}
