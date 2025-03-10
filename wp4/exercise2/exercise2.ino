/**
 * This program increases the position of a servo by 1 degree every second.
 *
 * Work Packages 4: Exercise 2 - ANALOG TIMER
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 611211
 **/

#include <Servo.h>  // Include the servo library

// Define the pin for the servo
#define SERVO_PIN A1

// Global variables for timer
int timer2 = 0;                  // Timer counter
int iCounter = 0;                // Counter for the number of times the interrupt has been called
int servoPosition = 0;           // Current position of the servo
unsigned long last_time_called;  // Last time the interrupt was called

// Create a servo object
Servo servoBase;

void setup() {
    servoBase.attach(SERVO_PIN);  // Attach the servo to pin 'SERVO_PIN'
    servoBase.write(0);           // Set the initial position of the servo to 0 degrees

    setup_timer_2();              // Setup timer
    Serial.begin(115200);         // Begin serial
    last_time_called = millis();  // Set the last time the interrupt was called to the current time
}

void loop() {
    // Do nothing
}

// Inspiration taken from course material:
// https://www.tinkercad.com/things/hqsDje5Qtdv?sharecode=CVIAWPHOUN6TuzFbgOV2ztOiFeXxdcmmXmHZHbqg57o
//
// Changes made:
// - Use timer2 instead of timer1
//
// This function sets up timer 2 to call an interrupt every 16ms
void setup_timer_2() {
    cli();  // Stop interrupts

    TCCR2A = 0;  // set entire TCCR2A register to 0
    TCCR2B = 0;  // same for TCCR2B
    TCNT2 = 0;   // initialize counter value to 0

    OCR2A = 250;                                        // set compare match register for 1hz increments
    TCCR2A |= (1 << WGM21);                             // turn on CTC mode
    TCCR2B |= (1 << CS20) | (1 << CS21) | (1 << CS22);  // set CS20, CS21, and CS22 bits for 1024 prescaler
    TIMSK2 |= (1 << OCIE2A);                            // enable timer compare interrupt

    sei();  // Allow interrupts
}

// Interrupt service routine for timer1 compare match A
ISR(TIMER2_COMPA_vect) {
    cli();                                  // Stop interrupts
    unsigned long current_time = millis();  // Get the current time

    iCounter++;  // Increment the counter

    // ISR gets called once every 16ms, so we need to increment the counter 64 times to get ~1024ms ~= 1 second.
    if (iCounter < 64) {
        return;  // This is to ensure that the servo is only updated every 64 interrupts
    }
    iCounter = 0;  // Reset the counter

    servoPosition = (servoPosition + 1) % 180;  // Increment the servo position by 1 degree (0-180 degrees)

    servoBase.write(servoPosition);  // Set the servo to the current position

    // Print the time since the last interrupt was called
    String message;  // Variable to store the message
    message = "Called: " + String(current_time - last_time_called) + "ms ago. ";
    message += "(Current time: " + String(current_time) + " ms, ";
    message += "Previous call: " + String(last_time_called) + "ms, ";
    message += "Servo position: " + String(servoPosition) + " degrees)";

    Serial.println(message);  // Print the message

    last_time_called = current_time;  // Update the last time the interrupt was called

    sei();  // Allow interrupts
}
