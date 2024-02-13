#include <ctype.h>   // Used for atoi()
#include <stdio.h>   // Used for printf()
#include <stdlib.h>  // Used for malloc()
#include <string.h>  // Used for strcpy(), strlen()

// Function declarations
int exit_and_free(char* input, char* err_message);  // Function to exit the program and free the memory
void copy_string(char* input, int free_mem);        // Function to copy the input string
char* copy_String_with_strcpy(char* string);        // Function to copy the input string with strcpy()
char* copy_String_with_loop(char* string);          // Function to copy the input string with a loop

/**
 * This program
 *
 * Work Packages 4: Exercise 6 - ARRAYS AND FILES
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/
int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (strlen(argv[1]) > 20) {
            printf("The input is too long.\n");
            return 1;
        }

        copy_string(argv[1], 0);

    }

    else {
        char* input = (char*)malloc(20 * sizeof(char));
        // If there are no command-line arguments, read a line from stdin
        if (fgets(input, 20, stdin) == NULL) {
            exit_and_free(input, "Error reading input.\n");
        }

        // After reading from the file...
        fclose(stdin);

        // Reopen stdin to read from the terminal
        stdin = fopen("/dev/tty", "r");
        if (stdin == NULL) {
            perror("Error reopening stdin");
            exit(EXIT_FAILURE);
        }

        copy_string(input, 1);
    }

    return 0;
}

int exit_and_free(char* input, char* err_message) {
    printf("%s", err_message);
    free(input);
    return 1;
}

void copy_string(char* input, int free_mem) {
    printf("Input: %s\n", input);

    printf("Copy with strcpy or loop? (1/2): ");
    char choice[2];
    scanf("%s", choice);
    while (atoi(choice) != 1 && atoi(choice) != 2) {
        printf("Invalid input. Please enter 1 or 2: ");
        scanf("%s", choice);
    }

    char* copy;

    if (atoi(choice) == 1) {
        copy = copy_String_with_strcpy(input);
        if (copy == NULL) {
            exit_and_free(input, "Error allocating memory for copy.\n");
        }
        printf("Copy with strcpy: %s\n", copy);
    }

    else {
        copy = copy_String_with_loop(input);
        if (copy == NULL) {
            exit_and_free(input, "Error allocating memory for copy.\n");
        }
        printf("Copy with loop: %s\n", copy);
    }

    if (free_mem) {
        free(input);
    }
    free(copy);
}

char* copy_String_with_strcpy(char* string) {
    char* copy = (char*)malloc(strlen(string) * sizeof(char));
    if (copy == NULL) {
        return NULL;
    }

    strcpy(copy, string);
    return copy;
}

char* copy_String_with_loop(char* string) {
    char* copy = (char*)malloc(strlen(string) * sizeof(char));
    if (copy == NULL) {
        return NULL;
    }

    for (int i = 0; i < strlen(string); i++) {
        copy[i] = string[i];
    }

    return copy;
}