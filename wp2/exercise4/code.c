#include <ctype.h>   // Used for isdigit()
#include <stdio.h>   // Used for printf(), scanf()
#include <stdlib.h>  // Used for atoi()

// Enum to store the input values order for the input arguments / packing order
enum INPUT {
    ENGINE_ON = 1,
    GEAR_POS,
    KEY_POS,
    BRAKE1,
    BREAK2
};

enum MAX_RANGE {
    ENGINE_ON_MAX = 1,
    GEAR_POS_MAX = 4,
    KEY_POS_MAX = 2,
    BRAKE1_MAX = 1,
    BREAK2_MAX = 1
};

enum BIT_SIZE {
    ENGINE_ON_SIZE = 1,
    GEAR_POS_SIZE = 3,
    KEY_POS_SIZE = 2,
    BRAKE1_SIZE = 1,
    BREAK2_SIZE = 1
};

/**
 * This program
 *
 * Work Packages 2: Exercise 4 - BITPACKING
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/
int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Invalid number of arguments, expected 5, got %d\n", argc - 1);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (!isdigit(argv[i][0]) && atoi(argv[i]) < 0) {
            printf("Error: Argument %d is not a number or less than 0\n", i);
            return 1;
        }
    }
    for
}