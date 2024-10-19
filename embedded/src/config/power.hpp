#include <Arduino.h>
#include "pins.h"

void powerInitializer()
{
    for (const int pin : pin_LOW)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, LOW);
    }
    for (const int pin : pin_HIGH)
    {
        pinMode(pin, OUTPUT);
        digitalWrite(pin, HIGH);
    }
    for (const int pin : pin_INPUT_PULLUP)
    {
        pinMode(pin, INPUT_PULLUP);
    }
}