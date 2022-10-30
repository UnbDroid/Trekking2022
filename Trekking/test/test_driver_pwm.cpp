
#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>

MotorDC motorRight(pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1);
MotorDC motorLeft(pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);

void incL()
{   
    motorLeft.encSignal();
}

void incR()
{
    motorRight.encSignal();
}

void setup()
{
    Serial.begin(9600);
}

void loop()
{

    for(int i = 0; i < 100; i+= 10)
    {
        moveAll(100-i, &motorLeft, &motorRight);
        delay(500);    
    }
    
    for(int i = 0; i < 100; i+= 10)
    {
        moveRevAll(100-i, &motorLeft, &motorRight);
        delay(500);    
    }
}
