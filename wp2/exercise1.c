// Includes
#include <ctype.h>   // Used for isdigit()
#include <stdio.h>   // Used for printf(), scanf()
#include <stdlib.h>  // Used for atoi()

// Enum to store directions
enum DIRECTION {
    NORTH,
    EAST,
    SOUTH,
    WEST
};

typedef struct {
    int x_pos;           // X coordinate of the robot.
    int y_pos;           // Y coordinate of the robot.
    enum DIRECTION dir;  // Direction the robot is facing.
} ROBOT;

// Global variables
const int MIN_CORD = 0;     // Minimum allowed value for coordinate.
const int MAX_CORD = 99;    // Maximum allowed value for coordinate.
const char END_CHAR = 'q';  // Character to indicate that the program should end once inputted.

// Function declarations
void set_coordinates(ROBOT* robot);
void read_coordinate(int* coordinate);
int read_commands(ROBOT* robot);
void move(ROBOT* robot);
void turn(ROBOT* robot);
char* direction_to_string(enum DIRECTION dir);

/**
 * This program takes starting coordinates, then following that, takes a set of command inputs to move around the x and y axises.
 *
 * Work Packages 2: Exercise 1 - ROBOT
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 2456372
 **/
int main(int argc, char* argv[]) {
    ROBOT robot;                             // Initialize robot struct variable.
    robot.dir = NORTH;                       // Set default direction to NORTH.
    int run = 1;                             // Set run to 1 (true)
    while (run) {                            // While run is true, keep looping
        set_coordinates(&robot);             // Call function 'set_coordinates()' to set the starting coordinates.
        int buffer = read_commands(&robot);  // Call function 'read_commands()' to read the commands, set return to buffer to still print the coordinates & direction.
        printf("Robot X-pos: %d\n", robot.x_pos);
        printf("Robot Y-pos: %d\n", robot.y_pos);
        printf("Robot dir: %s\n", direction_to_string(robot.dir));
        run = buffer;  // Set run to the return from 'read_commands()' incase the user inputs 'END_CHAR' ('q') to quit program (end loop).
    }
    return 0;  // Exit program.
}

// Function to set coordinates for the parameter pointer to a ROBOT struct.
void set_coordinates(ROBOT* robot) {
    printf("Enter starting coordinate X for the robot: ");
    read_coordinate(&robot->x_pos);

    printf("Enter starting coordinate Y for the robot: ");
    read_coordinate(&robot->y_pos);
    return;
}

// Function to read coordinates from user input. Sets read value to the parameter pointer to an int.o
void read_coordinate(int* coordinate) {
    char input[100] = {0};  // Input buffer for 'x' position.
    scanf("%s", input);
    while (isdigit(*input) == 0 || atoi(input) < MIN_CORD || atoi(input) > MAX_CORD) {
        printf("Invalid input, please enter a number between 0 and 99: ");
        scanf("%s", input);
    }
    *coordinate = atoi(input);
}

// Function to read commands from user input. Calls functions 'move()' and 'turn()' or 'return 0' depending on input.
int read_commands(ROBOT* robot) {
    printf("Enter commands (m = move, t = turn, q = quit): \n");
    char input[255] = {0};  // Input buffer for 'x' position.
    scanf("%s", input);

    int i = 0;
    while (input[i] != '\0') {
        switch (input[i]) {
            case 'm':         // if case is m
                move(robot);  // call the move function
                break;        // break out of switch
            case 't':         // if case is t
                turn(robot);  // call the turn function
                break;        // break out of switch
            case 'q':         // if case is q
                return 0;     // return 0
        }
        i++;  // Increment i by 1o
    }
    return 1;  // return 1
}

// Function to move the robot in the direction it is facing.
void move(ROBOT* robot) {
    switch (robot->dir) {
        case NORTH:          // If dir is north:
            robot->y_pos++;  // Increment y_pos by 1 to move robot north
            break;
        case EAST:           // If dir is east:
            robot->x_pos++;  // Increment x_pos by 1 to move robot east
            break;
        case SOUTH:          // If dir is south:
            robot->y_pos--;  // Decrement y_pos by 1 to move robot south
            break;
        case WEST:           // If dir is west:
            robot->x_pos--;  // Decrement x_pos by 1 to move robot west
            break;
    }
}

// Function to turn the robot 90 degrees clockwise.
void turn(ROBOT* robot) {
    switch (robot->dir) {
        case NORTH:             // If case: NORTH:
            robot->dir = EAST;  // Set dir of robot to EAST
            break;
        case EAST:               // if case: EAST:
            robot->dir = SOUTH;  // Set dir of robot to SOUTH
            break;
        case SOUTH:             // If case: SOUTH:
            robot->dir = WEST;  // Set dir of robot to WEST
            break;
        case WEST:               // If case: WEST:
            robot->dir = NORTH;  // Set dir of robot to NORTH
            break;
    }
}

// Function to return a string depending on the parameter enum DIRECTION.
char* direction_to_string(enum DIRECTION dir) {
    switch (dir) {
        case NORTH:          // if case is NORTH
            return "NORTH";  // return "NORTH";
        case EAST:           // if case is EAST
            return "EAST";   // return "EAST";
        case SOUTH:          // if case is SOUTH
            return "SOUTH";  // return "SOUTH";
        case WEST:           // if case is WEST
            return "WEST";   // return "WEST";
    }
}
