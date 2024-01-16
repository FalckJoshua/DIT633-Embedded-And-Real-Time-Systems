// (C) William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, group: 8 (2024)
// Work package 0
// Exercise 1
// Submission code: 2759
#include <stdio.h>
// Main function in the program, no program arguments supported
int main(int argc, char *argv[]) {

    //Check if any argument has been given
    if (argc < 2) {
        printf("Error, missing argument! Use '-h' for help \n");
        return 0;
    }
    // Check if there are more than one argument
    if (argc > 2) {
        printf("Error, too many arguments! Use '-h' for help \n");
        return 0;
    }


    // argv[1] is the first argument, if it is "-h", print help
    // argv[1][0] is the first character in the first argument, i.e '-'
    // argv[1][1] is the second character in the first argument, i.e 'h'
    if (argv[1][0] == '-' && argv[1][1] == 'h') {
        printf("Type your name using one word as argument \n");
        return 0;
    }

    // Print a string to the console
    printf("Hello World! - I'm %s  \n", argv[1]);
    return 0;
}