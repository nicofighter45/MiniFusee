#include <Servo.h>
#include "../config/pins.h"

class Parachute
{
private:
    const int initial_angle, final_angle, pin;
    Servo servomotor;
    bool deployed = false;

public:
    Parachute() : initial_angle(0), final_angle(90), pin(pin_parachute) {}

    void initialize();

    void deploy();

    void retract();
};
