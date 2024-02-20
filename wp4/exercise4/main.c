// Includes
#include <ctype.h>  // Used for isdigit()
#include <stdio.h>  // Used for printf(), scanf()

// Function Declarations
void print_array(int tab[], int size);               // Function to print the array
int search_number(int number, int tab[], int size);  // Function to search for a number in the array
void sort(int number, int tab[]);                    // Function to sort the array
void bubble_sort(int number, int tab[]);             // Function to sort the array using bubble sort
void selection_sort(int number, int tab[]);          // Function to sort the array using selection sort

/**
 * This program searches for numbers in an array and sorts the array using bubble sort or selection sort.
 *
 * Work Packages 4: Exercise 4 - LISTS
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 611211
 **/
int main(int argc, char* argv[]) {
    int array_size = 10;                                 // Size of the array
    int array[] = {1, 2, 34, 5, 67, 3, 23, 12, 13, 10};  // Array of numbers

    int is_10_in_array, is_34_in_array, is_100_in_array;  // Variables to store the result of the search

    print_array(array, array_size);  // Call function to print the array

    // Check if the numbers are in the array and print the result
    // ------------------------------------------------------------
    is_10_in_array = search_number(10, array, array_size);
    printf("Is 10 in the array? %d\n", is_10_in_array);

    is_34_in_array = search_number(34, array, array_size);
    printf("Is 34 in the array? %d\n", is_34_in_array);

    is_100_in_array = search_number(100, array, array_size);
    printf("Is 100 in the array? %d\n", is_100_in_array);
    // ------------------------------------------------------------

    sort(array_size, array);  // Call function to sort the array

    print_array(array, array_size);  // Call function to print the array

    // Check if the numbers are in the array after sorting and print the result
    // ------------------------------------------------------------
    is_10_in_array = search_number(10, array, array_size);
    printf("Is 10 in the array? %d\n", is_10_in_array);

    is_34_in_array = search_number(34, array, array_size);
    printf("Is 34 in the array? %d\n", is_34_in_array);

    is_100_in_array = search_number(100, array, array_size);
    printf("Is 100 in the array? %d\n", is_100_in_array);
    // ------------------------------------------------------------

    return 0;  // Exit program, indicate success
}

// Function to print the array
void print_array(int tab[], int size) {
    printf("Array: ");                // Print the array:
    for (int i = 0; i < size; i++) {  // Loop through the array
        printf("%d ", tab[i]);        // Print the number at current index
    }                                 // End loop
    printf("\n");                     // Print newline
}

// Function to search for a number in the array
int search_number(int number, int tab[], int size) {
    for (int i = 0; i < size; i++) {  // Loop through the array
        if (tab[i] == number) {       // If the number is found
            return i;                 // Number found
        }
    }

    return -1;  // Number not found
}

// Function to sort the array
void sort(int number, int tab[]) {
    printf("Use bubble sort (1) or selection sort (2) to sort the array?\n");

    char buffer = 0;        // Buffer to store user input
    scanf(" %c", &buffer);  // Read user input

    if (isdigit(buffer) && (buffer == '1' || buffer == '2')) {  // Check if the input is a digit and if that digit is 1 or 2

        if (buffer == '1') {           // If the input is 1:
            bubble_sort(number, tab);  // Call bubble_sort() function to sort the array
        }

        else {                            // Else, the input is 2:
            selection_sort(number, tab);  // Call selection_sort() function to sort the array
        }

    }

    else {                          // If the input is not a digit or not 1 or 2
        printf("Invalid input\n");  // Error message
        sort(number, tab);          // Recursive call to sort() function
    }
}

// Bubble sort implementation
void bubble_sort(int number, int tab[]) {
    printf("Sorting with: Bubble sort\n");

    int swapped;  // Variable to store if the array is sorted

    for (int i = 0; i < number - 1; i++) {  // Loop through the array

        swapped = 0;  // Set swapped to 0

        for (int j = 0; j < number - i - 1; j++) {  // Loop through the array
            if (tab[j] > tab[j + 1]) {              // If the current number is greater than the next number:

                // Swap the numbers
                int temp = tab[j];
                tab[j] = tab[j + 1];
                tab[j + 1] = temp;

                swapped = 1;  // Set swapped to 1
            }
        }

        if (!swapped) {  // If the array is sorted (no swaps in current iteration)
            break;       // Break the loop
        }
    }
}

// Selection sort implementation
void selection_sort(int number, int tab[]) {
    printf("Sorting with: Selection sort\n");
    for (int i = 0; i < number - 1; i++) {  // Loop through the array

        int min_index = i;  // Set the minimum index to the current index

        for (int j = i + 1; j < number; j++) {  // Loop through the array

            if (tab[j] < tab[min_index]) {  // If the current number is less than the number at the minimum index:
                min_index = j;              // Set the minimum index to the current index
            }
        }

        // Swap minimum number with the current 'first' number
        int temp = tab[min_index];
        tab[min_index] = tab[i];
        tab[i] = temp;
    }
}
