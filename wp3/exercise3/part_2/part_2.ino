/**
 * This program scans a 4x4 keypad and prints the pressed key to the serial monitor.
 *
 * Work Packages 3: Exercise 3 - KEYBOARD SCANNING
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 362789
 **/

// Matrix for characters for the 4x4 keypad
char char_matrix[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

int row_pins[4] = {11, 10, 9, 8};  // Pins for the rows
int col_pins[4] = {7, 6, 5, 4};    // Pins for the columns

void setup() {
    Serial.begin(9600);                      // Start serial communication
    for (int i = 0; i < 4; i++) {            // Loop through each row and column:
        pinMode(row_pins[i], OUTPUT);        // Set row pins to OUTPUT
        digitalWrite(row_pins[i], HIGH);     // Set row pins to HIGH
        pinMode(col_pins[i], INPUT_PULLUP);  // Set column pins to INPUT_PULLUP
    }
}

void loop() {
    char key = get_key();     // Get the key from the keypad
    if (key != '\0') {        // If a key is pressed:
        Serial.println(key);  // Print the key to the serial monitor
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
