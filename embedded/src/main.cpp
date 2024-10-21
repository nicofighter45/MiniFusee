#include <Arduino.h>
#include "parts/parachute.hpp"
#include "parts/accelerometer.hpp"
#include "parts/radio_client.hpp"
#include "config/serial.hpp"
#include "config/power.hpp"
#include "calculus/integrator.hpp"
#include "calculus/vector.hpp"

// define by user
const int time_before_deployment = 6; // in seconds
const int time_before_turn_up = 100;    // in ms
const int time_between_values = 10;     // in milliseconds

// needed for calculus
Vector previous_acceleration(0, 0, 0);
Vector previous_speed(0, 0, 0);
int previous_timing = 0;
int launch_instant = -1; // in ms
bool can_we_measure = false;

// comoponents
Parachute parachute;
Accelerometer accelerometer;

// setting up
void setup()
{
  powerInitializer();
  delay(time_before_turn_up);
  parachute.initialize();
  serialInitializer();
  accelerometer.initialize();
  can_we_measure = initialize_radio() && accelerometer.isItOnline();

  delay(time_before_turn_up);
  Serial.println("Setup done");
}

int time = 0;
uint8_t* bytes = new uint8_t[160];
void loop()
{

  // start of loop
  if (launch_instant == -1 && digitalRead(pin_deployment) == HIGH)
  {
    Serial.println("Launch detected");
    launch_instant = millis();
  }

  // Calculus
  if (can_we_measure)
  {
    int timing = millis();
    Vector *acceleration = accelerometer.actualizeAccelerationValues();

    float time_space = (timing - previous_timing);
    // Vector speed = get_speed_from_acceleration(previous_acceleration, *acceleration, time_space);
    // Vector position = get_position_from_speed(previous_speed, speed, time_space);

    float x = acceleration->getX();
    float y = acceleration->getY();
    float z = acceleration->getZ();
    int step = 16*(time%10);

    memcpy(bytes + step, &x, 4);
    memcpy(bytes + 4 + step, &y, 4);
    memcpy(bytes + 8 + step, &z, 4);
    memcpy(bytes + 12 + step, &time_space, 4);

    if (time % 10 == 9)
    {
      send_byte(bytes);
    }

    previous_acceleration = *acceleration;
    // previous_speed = speed;
    previous_timing = timing;
  }

  // end of loop
  if (launch_instant != -1 && millis() - launch_instant > time_before_deployment * 1000)
  {
    parachute.deploy();
  }

  delay(time_between_values);
  time++;
}