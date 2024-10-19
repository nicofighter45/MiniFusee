#include <Arduino.h>
#include "parts/parachute.hpp"
#include "parts/accelerometer.hpp"
#include "parts/radio_client.hpp"
#include "config/serial.hpp"
#include "config/power.hpp"
#include "calculus/integrator.hpp"
#include "calculus/vector.hpp"

// define by user
const int time_before_deployment = 6.5; // in seconds
const int time_before_turn_up = 100;    // in ms
const int time_between_values = 10;     // in milliseconds

// needed for calculus
Vector previous_acceleration(0, 0, 0);
Vector previous_speed(0, 0, 0);
int previous_timing = 0;
int launch_instant = -1; // in ms

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
  // initialize_radio();

  delay(time_before_turn_up);
  Serial.println("Setup done");
}

void loop()
{

  // start of loop
  if (launch_instant == -1 && digitalRead(pin_deployment) == HIGH)
  {
    Serial.println("Launch detected");
    launch_instant = millis();
  }

  // Calculus
  int timing = millis();
  Vector *acceleration = accelerometer.actualizeAccelerationValues();

  int time_space = (timing - previous_timing) / 1000.0;
  Serial.println(time_space);
  Vector speed = get_speed_from_acceleration(previous_acceleration, *acceleration, time_space);
  Vector position = get_position_from_speed(previous_speed, speed, time_space);
  send_vector(speed);

  // end of loop
  previous_acceleration = *acceleration;
  previous_speed = speed;
  previous_timing = timing;

  if (launch_instant != -1 && millis() - launch_instant > time_before_deployment * 1000)
  {
    parachute.deploy();
  }

  delay(time_between_values);
}