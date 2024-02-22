/**
 * This program
 *
 * Work Packages 5: Exercise 2 - TEMPERATURE METER
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: 326798
 **/

// LED pins
#define LED1_PIN 12
#define LED2_PIN 11
#define LED3_PIN 10
#define LED4_PIN 9
#define LED5_PIN 8

// LED temperature thresholds
const int LED_THRESHOLDS[] = {25, 27, 29, 31, 33};

// Temperature sensor pin
#define TEMP_PIN A0

// Taken from course material:
// https://www.tinkercad.com/things/hqsDje5Qtdv?sharecode=CVIAWPHOUN6TuzFbgOV2ztOiFeXxdcmmXmHZHbqg57o
//
// Timer definitions
#define PRESCALER 1024        // Used for dictating speed of timer according to (timer speed (Hz)) = (Arduino clock speed (16MHz)) / prescaler
#define INTERRUPT_FREQ 1      // Define interrupt frequency
#define CLOCK_SPEED 16000000  // Clock speed of the Arduino Uno
#define TIMER1_MAX 65535      // Max counter value for timer1
#define TIMER1_LOW 257        // Lowest counter value for timer1

// Global variables for timer
int timer1 = 0;
int iCounter = 0;

void setup() {
    // Initialize LED pins
    pinMode(LED1_PIN, OUTPUT);
    pinMode(LED2_PIN, OUTPUT);
    pinMode(LED3_PIN, OUTPUT);
    pinMode(LED4_PIN, OUTPUT);
    pinMode(LED5_PIN, OUTPUT);

    pinMode(TEMP_PIN, INPUT);  // Initialize temperature sensor pin

    setup_timer_1();     // Setup timer
    Serial.begin(9600);  // Begin serial
}

void loop() {
}

// Taken from course material:
// https://www.tinkercad.com/things/hqsDje5Qtdv?sharecode=CVIAWPHOUN6TuzFbgOV2ztOiFeXxdcmmXmHZHbqg57o
//
// Original comment:
/*
 * This function sets up timer1 on an Arduino Uno
 * Built on top of: https://www.instructables.com/Arduino-Timer-Interrupts/
 * Sets timer1 interrupt at 1Hz = 1 second = 1 cycle per second
 */
void setup_timer_1() {
    cli();  // stop interrupts

    TCCR1A = 0;  // set entire TCCR1A register to 0
    TCCR1B = 0;  // same for TCCR1B
    TCNT1 = 0;   // initialize counter value to 0

    // calculate at which point to stop the counter and set to int:
    timer1 = (CLOCK_SPEED / (PRESCALER * INTERRUPT_FREQ)) - 1;
    // timer1 = (CLOCK_SPEED / (INTERRUPT_FREQ)) - 1;
    //  timer1 = 16 000 000 / 65535

    if (timer1 >= TIMER1_MAX) {                                                            // if value went above max value
        timer1 = TIMER1_MAX;                                                               // set timer to max allowed value
        Serial.println((String) "timer1 was set too high and was changed to: " + timer1);  // notify user
    } else if (timer1 <= TIMER1_LOW) {                                                     // if value went below lowest value
        timer1 = TIMER1_LOW;                                                               // set timer to max allowed value
        Serial.println((String) "timer1 was set too low and was changed to: " + timer1);   // notify user
    }

    OCR1A = timer1;                       // set compare match register for 1hz increments
    TCCR1B |= (1 << WGM12);               // turn on CTC mode
    TCCR1B |= (1 << CS12) | (1 << CS10);  // set CS10 and CS12 bits for 1024 prescaler
    TIMSK1 |= (1 << OCIE1A);              // enable timer compare interrupt

    sei();  // allow interrupts
}

// Interrupt service routine for timer1 compare match A
ISR(TIMER1_COMPA_vect) {
    cli();  // Disable interrupts

    // Read value from module connected at pin A0
    int V_input = analogRead(TEMP_PIN);
    // Calculate thermometer resistance by comparing it to the modules onboard 10K-ohm resistor
    float R_ohms = 10000 * (1023.0 / (float)V_input - 1.0);
    // Calculate temperature in Celsius
    int temp = (1.0 / (0.001129148 + (0.000234125 * log(R_ohms)) + 0.0000000876741 * log(R_ohms) * log(R_ohms) * log(R_ohms))) - 273.15;

    Serial.println(temp);  // Print temperature to serial monitor

    for (int i = 0; i < 5; i++) {  // Iterate over the LED pins

        // Turn on the LED if the temperature is above the threshold
        // 'LED1_PIN - i' is used to iterate over the LED pins, first LED is highest PIN (12), last LED is lowest PIN (8)
        // Ternary operator is used to set the LED to HIGH if the temperature is above the threshold, otherwise LOW
        digitalWrite(LED1_PIN - i, temp >= LED_THRESHOLDS[i] ? HIGH : LOW);
    }

    sei();  // Allow interrupts
}
