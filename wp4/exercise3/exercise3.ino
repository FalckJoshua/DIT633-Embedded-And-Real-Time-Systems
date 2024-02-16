/**
 * This program reads the temperature every 1~ second and lights up the corresponding LED on a LED ring.
 *
 * Work Packages 4: Exercise 4 - ADDRESSABLE LEDS
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/

#include <Adafruit_NeoPixel.h>  // Include the Adafruit_NeoPixel library

#define RED_LED_PIN 8  // Red LED pin
#define TEMP_PIN A0    // Temperature sensor pin
#define LED_COUNT 12   // Number of LEDs in the ring
#define RING_PIN 2     // Pin for the LED ring

// Global variables for timer
int timer2 = 0;                  // Timer counter
int iCounter = 0;                // Counter for the number of times the interrupt has been called
int servoPosition = 0;           // Current position of the servo
unsigned long last_time_called;  // Last time the interrupt was called

const int temp_interval[12] = {-40, -25, -10, 5, 20, 35, 50, 65, 80, 95, 110, 125};  // Temperature intervals

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_COUNT, RING_PIN, NEO_GRB + NEO_KHZ800);  // Initialize the LED strip object from the Adafruit_NeoPixel library

void setup() {
    pinMode(RED_LED_PIN, OUTPUT);  // Initialize red LED pin
    pinMode(TEMP_PIN, INPUT);      // Initialize temperature sensor pin

    strip.begin();  // Call the begin method on the LED strip to start it

    setup_timer_2();  // Setup timer

    Serial.begin(115200);  // Begin serial

    last_time_called = millis();  // Set the last time the interrupt was called to the current time
}

void loop() {
    // Nothing to do here
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

    strip.clear();  // Clear the LED strip

    int temp = map(((analogRead(TEMP_PIN) - 20) * 3.04), 0, 1023, -40, 125);  // Read temperature from sensor

    int i;
    for (i = 0; i < 12; i++) {  // Iterate over the LED pins

        if (temp < temp_interval[i]) {  // If the temperature is less than the current interval
            break;                      // Break the loop
        }

        strip.setPixelColor(i, strip.Color(0, 150, 0));  // Set the color of the LED
    }

    if (i == 12) {
        digitalWrite(RED_LED_PIN, HIGH);  // Turn on the red LED
    } else {
        digitalWrite(RED_LED_PIN, LOW);  // Turn off the red LED
    }

    strip.show();  // Show the LED strip

    // Print the time since the last interrupt was called
    String message;  // Variable to store the message
    message = "Called: " + String(current_time - last_time_called) + "ms ago. ";
    message += "(Current time: " + String(current_time) + " ms, ";
    message += "Previous call: " + String(last_time_called) + "ms, ";
    message += "Temperature: " + String(temp) + ")";

    Serial.println(message);  // Print the message

    last_time_called = current_time;  // Update the last time the interrupt was called

    sei();  // Allow interrupts
}
