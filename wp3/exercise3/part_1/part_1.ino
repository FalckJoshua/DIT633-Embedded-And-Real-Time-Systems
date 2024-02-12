/**
 * This program reads the temperature from a sensor and prints it to the serial monitor.
 *
 * Work Packages 3: Exercise 3 - TEMPERATURE METER V 2.0
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/

int temp_pin = A0;  // Pin for temperature sensor

void setup() {
    Serial.begin(9600);      // Start the serial communication
    pinMode(temp_pin, INPUT);  // Set the temp_pin as input
}

void loop() {
    int temp_reading = analogRead(temp_pin);      // Read the temperature sensor
    float voltage = temp_reading * (5.0 / 1023);  // Convert to voltage
    voltage = voltage * 1000;                     // Turn to mV
    float temp = (voltage - 500) / 10;            // Convert to Celsius
    Serial.println(temp);                         // Print the temperature in Celsius
    delay(500);                                   // Wait for 500 millisecond(s)
}
