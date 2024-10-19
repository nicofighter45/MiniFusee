#include "Vector.hpp"

float Vector::getX() const
{
    return x;
}

float Vector::getY() const
{
    return y;
}

float Vector::getZ() const
{
    return z;
}

Vector::Vector(float x, float y, float z) : x(x), y(y), z(z) {}

Vector::Vector() : x(0), y(0), z(0) {}