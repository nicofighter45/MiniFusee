#include <Arduino.h>

void serialInitializer() //TODO delete in prod
{
  Serial.begin(9600);
  while (!Serial)
  {
    delay(10);
  }
  Serial.println("Serial initialized");
}