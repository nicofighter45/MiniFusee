#include "Vector.hpp"

Vector get_speed_from_acceleration(const Vector& acceleration_before, const Vector& acceleration_now, float time_step){
    return  acceleration_before + (acceleration_now - acceleration_before) * time_step;
}

Vector get_position_from_speed(const Vector& speed_before, const Vector& speed_now, float time_step){
    return  speed_before + (speed_now - speed_before) * time_step;
}
