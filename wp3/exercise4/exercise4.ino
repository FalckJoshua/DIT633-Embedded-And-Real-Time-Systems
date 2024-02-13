/**
 * This program scans a 4x4 keypad and prints the pressed key to the serial monitor, using the Keypad library.
 *
 * Work Packages 3: Exercise 4 - KEYBOARD SCANNING V 2.0
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/

// Includes
#include <Keypad.h>

// Matrix for characters for the 4x4 keypad
char char_matrix[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

const byte ROWS = 4;
const byte COLS = 4;
byte row_pins[ROWS] = {11, 10, 9, 8};  // Pins for the rows
byte col_pins[COLS] = {7, 6, 5, 4};    // Pins for the columns

Keypad keypad = Keypad(makeKeymap(char_matrix), row_pins, col_pins, ROWS, COLS);

void setup() {
    Serial.begin(9600);
}

void loop() {
    char key = keypad.getKey();

    if (key) {
        Serial.println(key);
    }
}