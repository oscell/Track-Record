/**
 * @file motor.cpp
 * @brief Control a motor with a Raspberry Pi using BCM2835 library.
 */

#include <iostream>
#include <bcm2835.h>

using namespace std;

class Motor {
public:
    /**
     * @brief Construct a new Motor object.
     *
     * @param pin The GPIO pin number that the motor is connected to.
     */
    Motor(uint8_t pin) : m_pin(pin)
    {
        bcm2835_gpio_fsel(m_pin, BCM2835_GPIO_FSEL_OUTP); // setting pin as output
    }

    /**
     * @brief Move the motor to a specified angle.
     *
     * This function moves the motor to the specified angle by generating
     * a PWM signal on the GPIO pin using the BCM2835 library.
     *
     * @param angle The desired angle of rotation in degrees.
     */
    void move(int angle)
    {
        int pulse;
        float on_time = 10.3 * angle + 340; // default original: 10.3 * angle + 546

        pulse = (int)(angle * 40.0 / 180.0) + 5;
        for (int i = 0; i < pulse; i++) {
            bcm2835_gpio_set(m_pin); // setting pin to high
            bcm2835_delayMicroseconds((int)on_time); // leaving it high for specified time
            bcm2835_gpio_clr(m_pin); // setting pin to low
            bcm2835_delayMicroseconds(20000 - (int)on_time); // 20000 = 20ms
        }
    }

private:
    uint8_t m_pin;
};

int main(int argc, char** argv)
{
    if (!bcm2835_init()) {
        cout << "Error: BCM2835 library not initialized" << endl;
        return 1;
    }

    Motor motor(18); // motor is connected to GPIO pin 18
    int angle = 0;
    int prev_angle = 0;

    while (true) {
        cout << "Enter integer for angle rotation: ";
        cin >> angle;

        motor.move(angle);
        prev_angle = angle;
    }

    bcm2835_close();
    return 0;
}
