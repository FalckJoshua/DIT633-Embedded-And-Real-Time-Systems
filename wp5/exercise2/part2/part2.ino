/**
 * This program reads the temperature and light intensity from sensors and turns on LEDs depending on the values.
 *
 * Work Packages 5: Exercise 2 - TEMPERATURE AND LIGHT METER
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: Submission code: 326798
 **/

// Pins for LEDs
int led_high_temp = 12;    // Declare the output pin for the high temperature LED
int led_normal_temp = 11;  // Declare the output pin for the normal temperature LED
int led_low_temp = 10;     // Declare the output pin for the low temperature LED

// Pins for input
int light_pin = A0;  // Declare the input pin for the light sensor
int temp_pin = A1;   // Declare the input pin for the temperature sensor

int timer = 1000;  // Delay between loops

const int low_temp_range[4] = {-40, -12, 1, 31};   // Low temp values
const int high_temp_range[4] = {-13, 0, 30, 125};  // High temp values
const int light_range[4] = {0, 20, 60, 90};       // Light percentage

int light;
int temp;

void setup() {
    Serial.begin(9600);  // Start the serial monitor with a baud rate of 9600

    pinMode(led_high_temp, OUTPUT);    // Set the led_temp pin as output
    pinMode(led_normal_temp, OUTPUT);  // Set the led_normal pin as output
    pinMode(led_low_temp, OUTPUT);     // Set the led_temp pin as output

    pinMode(light_pin, INPUT);  // Set the light_pin as input
    pinMode(temp_pin, INPUT);   // Set the temp_pin as input
}

void loop() {
    int light_input = analogRead(light_pin);                   // Read value from light sensor
    light = map(light_input, 1023, 0, 0, 100);  // Map the value to a percentage

    // Read value from module connected at pin A0
    int V_input = analogRead(temp_pin);
    // Calculate thermometer resistance by comparing it to the modules onboard 10K-ohm resistor
    float R_ohms = 10000 * (1023.0 / (float)V_input - 1.0);
    // Calculate temperature in Celsius
    temp = (1.0 / (0.001129148 + (0.000234125 * log(R_ohms)) + 0.0000000876741 * log(R_ohms) * log(R_ohms) * log(R_ohms))) - 273.15;

    Serial.print("Light: ");
    Serial.print(light);
    Serial.print("%, Temperature: ");
    Serial.print(temp);
    Serial.println("");

    // Depending on current light intensity, set allowed range for temperature
    if (light <= light_range[0]) {                              // Lowest interval, light <= 0
        LED_to_turn_on(low_temp_range[0], high_temp_range[0]);  // Call helper function
    }

    else if (light <= light_range[1]) {                         // Second lowest interval, light <= 20
        LED_to_turn_on(low_temp_range[1], high_temp_range[1]);  // Call helper function
    }

    else if (light <= light_range[2]) {                         // Second highest interval, light <= 60
        LED_to_turn_on(low_temp_range[2], high_temp_range[2]);  // Call helper function
    }

    else {                                                      // Highest interval, light <= 100
        LED_to_turn_on(low_temp_range[3], high_temp_range[3]);  // Call helper function
    }

    delay(timer);  // Delay 'timer' amount of miliseconds, to have a delay between each loop.

    // Turn off all lights for next iteration
    digitalWrite(led_high_temp, LOW);    // Set the high temperature LED to LOW (turn it off)
    digitalWrite(led_normal_temp, LOW);  // Set the normal temperature LED to LOW (turn it off)
    digitalWrite(led_low_temp, LOW);     // Set the low temperature LED to LOW (turn it off)
}

// Function to decide which LED to turn on, depending on if the current temperature is lower, between, or higher than the acceptable range
void LED_to_turn_on(int low, int high) {
    if (temp > high) {                        // If higher than allowed range:
        digitalWrite(led_high_temp, HIGH);    // Turn on high temperature LED
    } else if (temp < low) {                  // If lower than allowed range:
        digitalWrite(led_low_temp, HIGH);     // Turn on low temperature LED
    } else {                                  // Else, within allowed range:
        digitalWrite(led_normal_temp, HIGH);  // Turn on acceptable temperature LED
    }
}