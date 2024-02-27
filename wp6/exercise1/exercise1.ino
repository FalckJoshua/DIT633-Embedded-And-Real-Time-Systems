/**
 * This program is a simple implementation of a DC motor controller.
 * The user can input a desired position and the program will move the motor to that position.
 *
 * Work Packages 6: Exercise 1 - DC MOTOR CONTROLLER
 * DIT633 Development of embedded and Real-Time Systems
 *
 * Authors: William Andersson, Joshua Chiu Falck, Adam Faundez Laurokari, 2024
 * Group: 1
 * Submission code: TODO
 **/

#define ENCA 2  // Encoder A
#define ENCB 3  // Encoder B

#define PWM1 5  // Motor 1,
#define PWM2 6  // Motor 2, for

int pos = 0;  // Position in ticks
int deg = 0;  // Position in degrees

int degtarget = 0;  // Target position in degrees

int speed = 0;  // Desired motor speed

int kp = 15;    // Proportional constant for controller (tuning parameter)
int u_out = 0;  // output of controller

int e = 0;  // error
int a = 0;  // a-encoder signal
int b = 0;  // b-encoder signal

void setup() {
    Serial.begin(9600);           // Start serial communication
    pinMode(ENCA, INPUT_PULLUP);  // Set the encoder pins to INPUT_PULLUP
    pinMode(ENCB, INPUT_PULLUP);  // Set the encoder pins to INPUT_PULLUP
    pinMode(PWM1, OUTPUT);        // Set the motor pins to OUTPUT
    pinMode(PWM2, OUTPUT);        // Set the motor pins to OUTPUT

    attachInterrupt(digitalPinToInterrupt(ENCA), ISR_readEncoder, RISING);  // Attach the interrupt to the encoder pin

    // Start the motor, just a tiny little bit because otherwise TinkerCad dies....
    analogWrite(PWM2, 10);
    delay(200);  // TinkerCad bug
    analogWrite(PWM1, 10);
}

void loop() {
    // Check if motor rotated all the way around, and reset counter
    if (pos < -2299 || pos > 2299) {
        pos = 0;
    }

    // If deg is over 359, reduce it to 0-359 depending on the value
    if (deg > 359) {
        deg = deg - 360;
    }

    // Print current position
    Serial.print("The current position is: ");
    Serial.print(deg);
    Serial.print("\n");

    // Get input
    degtarget = getInput() + deg;

    // Print target position
    Serial.print("The target position is: ");
    Serial.print(degtarget);
    Serial.print("\n");

    // Calculate initial error
    e = degtarget - deg;

    // Loop until error is zero
    while (e) {
        // Map current position into degrees
        deg = map(pos, 0, 2299, 0, 360);

        // Get necessary speed signal
        speed = getAction(e);

        // Send speed signal to motor
        // Rotating clockwise
        if (speed >= 0) {
            if (speed < 100)  // motor does not react with too low inputs
                speed = 100;
            analogWrite(PWM2, 0);
            analogWrite(PWM1, speed);
        }

        // Rotating counter-clockwise
        else {
            if (-speed < 100)  // motor does not react with too low inputs
                speed = -100;
            analogWrite(PWM1, 0);
            analogWrite(PWM2, -speed);
        }

        // Calculate new error
        e = degtarget - deg;
    }

    if (e == 0) {
        // stop the motor from continously rotating
        analogWrite(PWM1, 10);
        delay(200);
        analogWrite(PWM2, 10);
    }
}

// Function to get input from user
int getInput() {
    int ready = 0;   // Flag to check if input is ready
    char buf[3];     // Buffer to store input
    int input = -1;  // Input variable

    Serial.print("Please enter the desired position: \n");

    while (!ready) {                       // Loop until input is ready
        ready = Serial.readBytes(buf, 3);  // Read input
        input = atoi(&buf[0]);             // Convert input to integer
    }

    return input;  // Return input
}

// Function to get the action signal
int getAction(int error) {
    u_out = kp * error;  // Calculate the output of the controller

    if (u_out > 254) {  // If the output is too high
        return 255;     // Return the maximum value
    }

    else if (u_out < -254) {  // If the output is too low
        return -255;          // Return the minimum value
    }

    else {             // Else
        return u_out;  // Return the output
    }
}

// Interrupt service routine to read the encoder
void ISR_readEncoder() {
    a = digitalRead(ENCA);  // Read the state of one of the encoder pins
    b = digitalRead(ENCB);  // Read the state of the other encoder pin

    if (a == HIGH && b == LOW) {  // If the encoder is moving clockwise
        pos++;                    // Increment the position
    } else {                      // Else, the encoder is moving counter-clockwise
        pos--;                    // Decrement the position
    }
}
