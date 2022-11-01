#include <Arduino.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <string.h>
#include <defines.h>

Gyro *giroscopio = new Gyro();

MotorDC motorLeft(pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1);
MotorDC motorRight(pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    // Inicializa o HMC5883
    Wire.beginTransmission(address);
    // Seleciona o modo
    Wire.write(0x02);
    // Modo de medicao continuo
    Wire.write(0x00);
    Wire.endTransmission();
}

void loop()
{
    delay(3000);
    // FUNCIONA COM ANGULOS DE -180 A +180
    turnDegreesGyro2(120, 90, HORARIO, &motorLeft, &motorRight, giroscopio);
}