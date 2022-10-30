#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>

void setup()
{
    Serial.begin(9600);
    pinMode(27, INPUT);
    pinMode(29, INPUT);
    pinMode(31, INPUT);
    pinMode(33, INPUT);
    pinMode(35, INPUT);

    pinMode(37, INPUT);
    pinMode(39, INPUT);
}

void loop()
{
    uint8_t sumBits = 0;
    uint8_t exp = 0;


    for(int i = 27; i < 40; i+=2) {
        sumBits += digitalRead(i) << exp;
        exp++;
    }

    Serial.println(sumBits);
}
