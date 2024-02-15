// Includes
#include <stdio.h>   // Used for printf
#include <stdlib.h>  // Used for rand
#include <time.h>    // Used for srand

// Constants
#define MAX 10  // Define the constant MAX to be used as the size of the array

// Function declarations
void generate_numbers(int *arr);  // Function to generate random numbers for each element in the array
void print_all(int *arr);         // Function to print all the elements in the array

/**
 * This program generates an array of size 'MAX' with random numbers between 1 and 99.
 * Afterwards, it prints random information about the array and its elements.
 * Lastly, it prints all the elements in the array and the value of each element multiplied by 2, using pointers.
 *
 * Work Packages 4: Exercise 5 - POINTERS AND ARRAYS
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 362789
 **/

int main(int argc, char *argv[]) {
    int arr[MAX];           // Initialize an array with MAX integer elements
    srand(time(NULL));      // Seed the random number generator with the current time
    generate_numbers(arr);  // Call the function to generate random numbers for each element in the array

    int integer_size = sizeof(int);

    printf("The value of the address of the array (pointer) is: %p\n", arr);
    printf("First integer in the array is (array[0]): %d\n", *arr);
    printf("The last integer in the array is: %d\n", arr[MAX - 1]);
    printf("The size of an integer (number of bytes) is: %d\n", integer_size);
    printf("The size of the whole array in bytes is: %d\n", integer_size * MAX);

    print_all(arr);  // Call the function to print all the elements in the array
}

// Function to generate random numbers for each element in the array
void generate_numbers(int *arr) {
    for (int i = 0; i < MAX; i++) {  // Loop through all the elements in the array
        arr[i] = rand() % 99 + 1;    // Generate and assign a random number between 1 and 99
    }
}

// Function to print all the elements in the array
void print_all(int *arr) {
    for (int i = 0; i < MAX; i++) {  // Loop through all the elements in the array

        // Print the current element (i) in the array and the value of the element by using an incremented pointer (arr + i)
        printf("arr[%d] = %3d. The value 2x is: %3d\n", i, *(arr + i), *(arr + i) * 2);
    }
}