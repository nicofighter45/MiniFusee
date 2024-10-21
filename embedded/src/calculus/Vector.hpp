#pragma once

class Vector
{
private:
    float x, y, z;

public:
    Vector();
    Vector(float x, float y, float z);
    float getX() const;
    float getY() const;
    float getZ() const;
};

inline Vector operator+(const Vector& vect1, const Vector& vect2) {
    return Vector(vect1.getX() + vect2.getX(), 
                    vect1.getY() + vect2.getY(),
                        vect1.getZ() + vect2.getZ());
}

inline bool operator==(const Vector& vect1, const Vector& vect2) {
    return vect1.getX() == vect2.getX() && vect1.getY() == vect2.getY() && vect1.getZ() == vect2.getZ();
}

inline Vector operator+=(const Vector& vect1, const Vector& vect2) {
    return vect1 + vect2;
}

inline Vector operator-(const Vector& vect1, const Vector& vect2) {
    return Vector(vect1.getX() - vect2.getX(),
        vect1.getY() - vect2.getY(),
        vect1.getZ() - vect2.getZ());
}

inline Vector operator-=(const Vector& vect1, const Vector& vect2) {
    return vect1 - vect2;
}

inline Vector operator*(const double scalar, const Vector& vect) {
    return Vector(scalar * vect.getX(),
                    scalar * vect.getY(),
                        scalar * vect.getZ());
}

inline Vector operator*(const Vector& vect, const double scalar) {
    return scalar * vect;
}

inline Vector operator*=(const Vector& vect, const double scalar) {
    return vect * scalar;
}

inline Vector operator/(const Vector& vect, const double scalar) {
    if (scalar == 0) {
        return Vector(0, 0, 0);
    }
    return Vector(vect.getX()/scalar,
                    vect.getY()/scalar,
                        vect.getZ()/scalar);
}

inline Vector operator/=(const Vector& vect, const double scalar) {
    return vect / scalar;
}