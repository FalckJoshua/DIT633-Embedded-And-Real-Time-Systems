/**
 * This program blinks an LED and turns on another LED when a button is pressed.
 *
 * Work Packages 3: Exercise 1 - SET-UP
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/

// Pin setup
int led_1 = 12;  // pin 12 for the first LED
int led_2 = 7;   // pin 7 for the second LED
int button = 2;  // pin 2 for the button

// Variables for time tracking
unsigned long tracker;  // to track the time
unsigned long current;  // to store the current time
int timer = 1000;       // delay for the first LED, 1 second

bool led_1_state;  // stores state of the 1st LED, true for ON, false for OFF
int button_state;  // stores state of the button, HIGH for pressed, LOW for not pressed

// Setup pins and variables
void setup() {
    pinMode(button, INPUT);  // set the button pin as input
    pinMode(led_1, OUTPUT);  // set the first LED pin as output
    pinMode(led_2, OUTPUT);  // set the second LED pin as output

    led_1_state = false;  // initialize the state of the first LED
    tracker = millis();   // initialize the tracker
}

void loop() {
    // --- First LED - Blinking ---
    current = millis();                 // get the current time
    if (current - tracker >= timer) {   // if the delay has passed:
        if (led_1_state) {              // if the LED is ON, turn it OFF
            led_1_state = false;        // update the state of the led to OFF (false)
            digitalWrite(led_1, LOW);   // turn the LED OFF
        } else {                        // if the LED is OFF, turn it ON
            led_1_state = true;         // update the state of the led to ON (true)
            digitalWrite(led_1, HIGH);  // turn the LED ON
        }
        tracker = current;  // update the tracker to the current time
    }

    // --- Second LED - Button Control ---
    button_state = digitalRead(button);  // read the state of the button
    if (button_state == HIGH) {          // if the button is pressed
        digitalWrite(led_2, HIGH);       // turn the LED ON
    } else {                             // if the button is not pressed
        digitalWrite(led_2, LOW);        // turn the LED OFF
    }
}