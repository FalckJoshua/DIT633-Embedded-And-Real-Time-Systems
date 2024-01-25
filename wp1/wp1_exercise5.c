#include <stdio.h>   // Used for printf(), scanf()
#include <stdlib.h>  // Used for rand()
#include <time.h>    // Used for time(), to seed srand()

#define MAXIMUM_VALUE 10            // Defines the maximum number of the values in the table
#define AMOUNT_OF_RANDOM_NUMBERS 5  // Defines the maximum value of random numbers

// ------ Function declarations ----------
// This function generates a set of random numbers
// and fills the table *tab with these numbers
void create_random(int *tab);
// This function takes the *tab of random numbers
// and creates a table with the frequency counts for these numbers
void count_frequency(int *tab, int *freq);
// This function takes the frequency count table
// and draws a histogram of the values in that frequency table
void draw_histogram(int *freq);

/**
 * This program generates an array filled with random numbers. It then counts the frequency of each number and draws a histogram in the terminal.
 *
 * Work Packages 1: Exercise 5 - POINTERS
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 315775
 **/
int main(int argc, char *argv[]) {
    int table[AMOUNT_OF_RANDOM_NUMBERS], n;  // Declare the 'table' array and the 'n' variable.
    int frequency[MAXIMUM_VALUE];            // Declare the 'frequency' array.

    srand(time(0));  // Initialize random number generator.

    create_random(table);               // Call create_random() to fill the 'table' array with random numbers.
    count_frequency(table, frequency);  // Call count_frequency() to fill the 'frequency' array with the frequency of each random generated number in the 'table' array.
    draw_histogram(frequency);          // Print a histogram of the frequency of random generated numbers.

    return 0;  // Exit program successfully.
}

// Function to generate random numbers for the 'table' array.
void create_random(int *tab) {                            // Function to generate random numbers.
    for (int i = 0; i < AMOUNT_OF_RANDOM_NUMBERS; i++) {  // Loop through the array and fill it with random numbers.
        tab[i] = rand() % (MAXIMUM_VALUE);                // Generate a random number between 0 and the maximum value. (Technically 0 to (MAXIMUM_VALUE - 1)).
    }
}

// Function to count the frequency of each random number.
void count_frequency(int *tab, int *freq) {
    for (int i = 0; i < MAXIMUM_VALUE; i++) {  // Loop through the array and set all values to 0 to avoid garbage values.
        freq[i] = 0;                           // Initialize the value to 0;
    }
    for (int i = 0; i < AMOUNT_OF_RANDOM_NUMBERS; i++) {  // Loop through 'table' array and add the frequency of it to the 'frequency' array.
        freq[tab[i]] = freq[tab[i]] + 1;                  // Use [i] to contain the frequency of the number i.
    }
}

// Function to print a histogram of the frequency of random generated numbers.
void draw_histogram(int *freq) {
    for (int i = 0; i < MAXIMUM_VALUE; i++) {    // Loop through all entries in the 'frequency' array.
        if (freq[i] > 0) {                       // If value is not 0 (it is not a number that was randomly generated), then:
            printf("%d    ", i);                 // Print the number.
            for (int j = 0; j < freq[i]; j++) {  // Loop through 0 and frequency value and:
                printf("x");                     // print a 'x' for each frequency.
            }
            printf("\n");  // Newline.
        }
    }
}
