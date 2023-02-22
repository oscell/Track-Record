#include <wiringPi.h>
#include <iostream>

#define SERVO_PIN 18 // The GPIO pin that the servo signal wire is connected to
#define PWM_RANGE 1024 // The PWM signal range for the servo motor

int main()
{
    // Initialize the wiringPi library
    wiringPiSetupGpio();

    // Set the SERVO_PIN as an output
    pinMode(SERVO_PIN, PWM_OUTPUT);

    // Set the PWM range for the servo motor
    pwmSetRange(PWM_RANGE);

    // Set the servo signal to its minimum position (0 degrees)
    pwmWrite(SERVO_PIN, 0);

    // Wait for the servo to move to the minimum position
    delay(1000);

    // Set the servo signal to its maximum position (360 degrees)
    pwmWrite(SERVO_PIN, PWM_RANGE);

    // Wait for the servo to move to the maximum position
    delay(1000);

    // Set the servo signal to the middle position (180 degrees)
    pwmWrite(SERVO_PIN, PWM_RANGE / 2);

    // Wait for the servo to move to the middle position
    delay(1000);

    // Stop the servo signal
    pwmWrite(SERVO_PIN, 0);

    return 0;
}
