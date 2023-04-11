#ifndef MOTOR_H
#define MOTOR_H

class Motor {
public:
    /**
     * @brief Construct a new Motor object.
     *
     * This constructor initializes the BCM2835 library and sets up the
     * motor on the specified GPIO pin.
     *
     * @param gpio_pin The GPIO pin to which the motor is connected.
     */
    Motor(int gpio_pin);

    /**
     * @brief Move the motor to a specified angle.
     *
     * This function moves the motor to the specified angle by generating
     * a PWM signal on the GPIO pin specified in the constructor using
     * the BCM2835 library.
     *
     * @param angle The desired angle of rotation in degrees.
     */
    void move(int angle);

private:
    int gpio_pin_; ///< The GPIO pin to which the motor is connected.
};

#endif // MOTOR_H
