/**
 * This program is a simple implementation of a keypad and an LED ring.
 * The user can input an address using the keypad and the program will check if the address is correct.
 * If the address is correct, the LED ring will light up in a green-blue mix and flash yellow.
 * If the address is incorrect, the LED ring will light up in red and flash red.
 * The program uses the Adafruit NeoPixel library to control the LED ring.
 *
 * Work Packages 6: Exercise 3 - STARGATE
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/

// Libraries
#include <Adafruit_NeoPixel.h>
#include <string.h>

// Definitions
#define LED_COUNT 24  // Number of LEDs in the ring
#define RING_PIN 2    // Pin for the LED ring

// Matrix for characters for the 4x4 keypad
char char_matrix[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

int row_pins[4] = {11, 10, 9, 8};  // Pins for the rows
int col_pins[4] = {7, 6, 5, 4};    // Pins for the columns

// Matrix for the correct address, 8 addresses with 7 characters each (7 characters + NULL character)
char correct_address[8][8] = {
    "1AC91BD",
    "342824A",
    "6D1732B",
    "52A64AC",
    "413553A",
    "34246CC",
    "23B393B",
    "9999999"};

char input[8];        // Array to store the input
int input_index = 0;  // Index for the input array

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, RING_PIN, NEO_GRB + NEO_KHZ800);  // Initialize the LED ring

void setup() {
    Serial.begin(9600);                      // Start serial communication
    for (int i = 0; i < 4; i++) {            // Loop through each row and column:
        pinMode(row_pins[i], OUTPUT);        // Set row pins to OUTPUT
        digitalWrite(row_pins[i], HIGH);     // Set row pins to HIGH
        pinMode(col_pins[i], INPUT_PULLUP);  // Set column pins to INPUT_PULLUP
    }
    strip.begin();  // Call the begin method on the LED strip to start it
    strip.clear();  // Clear the LED strip

    input[8] = '\0';  // Set the last character of the input array to NULL character
}

void loop() {
    char key = get_key();          // Get the key from the keypad
    if (key != '\0') {             // If a key is pressed:
        Serial.println(key);       // Print the key to the serial monitor
        input[input_index] = key;  // Set the input at the input index to the pressed key
        input_index++;             // Increment the input index

        strip.setPixelColor(input_index * 2, strip.Color(255, 255, 0));
        strip.setPixelColor(input_index * 2 - 1, strip.Color(255, 255, 0));
        strip.show();
    }

    if (input_index == 7) {               // If the input index is 7:
        check_address();                  // Call the check_address function
        input_index = 0;                  // Reset the input index to 0
        memset(input, 0, sizeof(input));  // Clear the input array
    }
}

char get_key() {
    char key = '\0';  // Initialize key to NULL character

    for (int i = 0; i < 4; i++) {        // Scan each row
        digitalWrite(row_pins[i], LOW);  // Set row pin to LOW

        for (int j = 0; j < 4; j++) {  // Read each column pin

            if (digitalRead(col_pins[j]) == LOW) {  // If the button is pressed:
                key = char_matrix[i][j];            // Get the key from the matrix
                delay(200);                         // Debounce delay
            }
        }

        digitalWrite(row_pins[i], HIGH);  // Set row pin back to HIGH
    }

    return key;  // Return the pressed key
}

// Function to check the address
void check_address() {
    strip.clear();  // Clear the LED strip

    int red = 0, green = 0, blue = 0, start_light = 0, correct = 1;  // Initialize variables

    for (int i = 0; i < 7; i++) {  // Loop through each character in the input

        for (int j = start_light; j < 24; j++) {  // Loop through each LED

            strip.setPixelColor(j % 24, strip.Color(red, green, blue));  // Set the color of the LED
            strip.show();                                                // Show the LED strip

            red = (red + 20) % 255;      // Increment red by 5 and take the modulo 255
            green = (green + 10) % 255;  // Increment green by 10 and take the modulo 255
            blue = (blue + 15) % 255;    // Increment blue by 15 and take the modulo 255

            delay(50);  // Delay for 100 milliseconds
        }

        if (i == 6) {  // If the last character is reached:
            break;     // Break the loop
        }              // The operation below is done differently for the last character

        strip.setPixelColor(start_light, strip.Color(0, 150, 0));      // Set the color of the LED to green
        strip.setPixelColor(start_light + 1, strip.Color(0, 150, 0));  // Set the color of the LED to green

        strip.show();  // Show the LED strip

        start_light = start_light + 2;  // Increment the start light by 2
    }

    // check if the input matches any address with strcmp
    for (int i = 0; i < 8; i++) {
        if (strcmp(input, correct_address[i]) == 0) {
            strip.setPixelColor(start_light, strip.Color(0, 150, 0));      // Set the color of the LED to green
            strip.setPixelColor(start_light + 1, strip.Color(0, 150, 0));  // Set the color of the LED to green

            strip.show();  // Show the LED strip

            delay(1000);  // Delay for 1000 milliseconds

            found_correct_address();  // Call the found_correct_address function
            return;                   // Return from the function
        }
    }

    strip.setPixelColor(start_light, strip.Color(150, 0, 0));      // Set the color of the LED to red
    strip.setPixelColor(start_light + 1, strip.Color(150, 0, 0));  // Set the color of the LED to red

    strip.show();  // Show the LED strip

    delay(1000);  // Delay for 1000 milliseconds

    found_wrong_address();  // Call the found_wrong_address function
    return;                 // Return from the function
}

// Function to indicate that the wrong address was found
void found_wrong_address() {
    for (int i = 0; i < 24; i++) {                       // Loop through each LED
        strip.setPixelColor(i, strip.Color(150, 0, 0));  // Set the color of the LED to red
        strip.show();                                    // Show the LED strip
        delay(100);                                      // Delay for 100 milliseconds
    }

    strip.clear();  // Clear the LED strip
    delay(500);     // Delay for 500 milliseconds
    strip.show();   // Show the LED strip

    for (int i = 0; i < 3; i++) {                            // Blink 5 times
        for (int j = 0; j < 24; j++) {                       // Loop through each LED
            strip.setPixelColor(j, strip.Color(255, 0, 0));  // Set the color of the LED to red
        }
        strip.show();  // Show the LED strip
        delay(500);    // Delay for 500 milliseconds

        strip.clear();  // Clear the LED strip
        strip.show();   // Show the LED strip
        delay(500);     // Delay for 500 milliseconds
    }

    // Cleanup
    strip.clear();  // Clear the LED strip
    strip.show();   // Show the LED strip
}

// Function to indicate that the correct address was found
void found_correct_address() {
    for (int i = 0; i < 24; i++) {                        // Loop through each LED
        strip.setBrightness(10 * i);                      // Set the brightness of the LED
        strip.setPixelColor(i, strip.Color(0, 69, 100));  // Set the color of the LED to a green-blue mix
        strip.show();                                     // Show the LED strip
        delay(100);                                       // Delay for 100 milliseconds
    }

    strip.setBrightness(255);  // Set the brightness to maximum

    // Flashing all LEDs
    for (int j = 0; j < 6; j++) {  // Repeat the flashing 6 times

        for (int i = 0; i < 24; i++) {  // Loop through each LED

            // Change color every other loop
            if (j % 2 == 0) {                                     // If j is even:
                strip.setPixelColor(i, strip.Color(0, 69, 100));  // Set the color of the LED to a green-blue mix
            }

            else {                                                 // If j is odd:
                strip.setPixelColor(i, strip.Color(255, 255, 0));  // Set the color of the LED to yellow
            }

            strip.show();  // Show the LED strip
        }

        delay(500);  // Delay for 500 milliseconds
    }

    // Cleanup
    strip.clear();  // Clear the LED strip
    strip.show();   // Show the LED strip
}