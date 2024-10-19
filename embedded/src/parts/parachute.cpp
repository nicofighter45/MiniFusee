#include "parachute.hpp"

void Parachute::initialize()
{
    servomotor.attach(pin);
    servomotor.write(initial_angle);
}

void Parachute::deploy()
{
    if(deployed)
    {
        return;
    }
    deployed = true;
    servomotor.write(final_angle);
}

void Parachute::retract()
{
    if (!deployed)
    {
        return;
    }
    deployed = false;
    servomotor.write(initial_angle);
}