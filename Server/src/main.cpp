#include <Arduino.h>
#include <SoftwareSerial.h>
#include <RH_RF95.h>

// Singleton instance of the radio driver
SoftwareSerial ss(2, 3);
RH_RF95 rf95(ss);

void setup()
{
  Serial.begin(9600);
  Serial.println("RF95 server test.");

  if (!rf95.init())
  {
    Serial.println("init failed");
    while (1)
      ;
  }
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
  // you can set transmitter powers from 5 to 23 dBm:
  // rf95.setTxPower(13, false);

  rf95.setFrequency(868.0);
}

const float g = 9.81 / 1000;

uint8_t len = 160;
uint8_t* buf = new uint8_t[len];
void loop()
{
  if (rf95.available())
  {
    // Should be a message for us now
    if (rf95.recv(buf, &len))
    {
      Serial.print("Values: ");
      for (int i = 0; i < 40; i++)
      {
        float value = 0;
        memcpy(&value, buf + i*4, 4);
        Serial.print(value);
        Serial.print(" ");
      }
      Serial.println(" ");
    }
    else
    {
      Serial.println("recv failed");
    }
  }
}