#include <Arduino.h>
#include <MotorDC.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <string.h>
#include <defines.h>

int firstReading = true;
int count = 0;
int valueRef;

MotorDC motorRight(pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);
MotorDC motorLeft(pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1);
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // stopAll(&motorLeft, &motorRight);
    // moveAll(10, &motorLeft, &motorRight);
    moveRevAll(40, &motorLeft, &motorRight);
}