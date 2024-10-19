#include <GY521.h>
#include "../calculus/Vector.hpp"

class Accelerometer
{
private:
    GY521 sensor;
    Vector vector = Vector(0, 0, 0);

public:
    Accelerometer() : sensor(0x68) {}
    void initialize();
    Vector* actualizeAccelerationValues();

};
