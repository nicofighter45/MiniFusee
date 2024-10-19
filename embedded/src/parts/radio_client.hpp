#include <SoftwareSerial.h>
#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include "../config/pins.h"
#include "../calculus/vector.hpp"

// Singleton instance of the radio driver
SoftwareSerial ss(pin_radio_1, pin_radio_2);
RH_RF95 rf95(ss);

void initialize_radio()
{
    Serial.println("RF95 client test.");
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

void send_message(float value)
{
    uint8_t len = 4;
    uint8_t data[len];
    memcpy(&data, &value, len);
    rf95.send(data, len);
    Serial.print("Sending packet value: ");
    Serial.print(value);
    Serial.print("  packet: ");
    Serial.println((char *)data);
    rf95.waitPacketSent();
}

void send_vector(Vector &vector)
{
    uint8_t len = 4;
    float x = vector.getX();
    float y = vector.getX();
    float z = vector.getX();
    uint8_t* data = new uint8_t[3 * len]; //dynamic allocation
    memcpy(data, &x, len);
    memcpy(data + len, &y, len);
    memcpy(data + 2*len, &z, len);
    rf95.send(data, 3 * len);
    Serial.print("Sending packet value: ");
    Serial.print(x);
    Serial.print(" ");
    Serial.print(y);
    Serial.print(" ");
    Serial.println(z);
    delete[] data; //free memory
}