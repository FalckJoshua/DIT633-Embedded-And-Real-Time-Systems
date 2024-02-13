// Includes
#include <stdio.h>  // Used for printf
#include <stdlib.h>
#include <time.h>  // Used for srand

// Function declarations
void generate_numbers(int *arr);
void print_all(int *arr);

const int MAX = 10;

/**
 * This program
 *
 * Work Packages 4: Exercise 5 - POINTERS AND ARRAYS
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/

int main(int argc, char *argv[]) {
    int arr[MAX];
    srand(time(NULL));
    generate_numbers(arr);

    printf("The value of the address of the array (pointer) is: %p\n", arr);
    printf("First integer in the array is (array[0]): %d\n", *arr);
    printf("The last integer in the array is: %d\n", arr[MAX - 1]);
    printf("The size of an integer (number of bytes) is: %lu\n", sizeof(int));
    printf("The size of the whole array in bytes is: %lu\n", sizeof(arr));

    print_all(arr);
}

void generate_numbers(int *arr) {
    for (int i = 0; i < MAX; i++) {
        arr[i] = rand() % 99 + 1;
    }
}

void print_all(int *arr) {
    for (int i = 0; i < MAX; i++) {
        printf("arr[%d] = %d. The value 2x is: %d\n", i, *(arr + i), *(arr + i) * 2);
    }
}