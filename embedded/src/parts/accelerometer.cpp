#include "accelerometer.hpp"
#include "../calculus/Vector.hpp"
#include <Wire.h>

void Accelerometer::initialize()
{
    Wire.begin();
    delay(100);
    if (sensor.wakeup() == false)
    {
        Serial.println("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
    }
}

Vector* Accelerometer::actualizeAccelerationValues()
{
    sensor.read();
    vector = Vector(sensor.getAccelX(), sensor.getAccelY(), sensor.getAccelZ());
    return &vector;
}
