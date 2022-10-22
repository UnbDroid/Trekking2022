#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>

int firstReading = true;
int count = 0;
int valueRef;

MotorDC motorRight(pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1);
MotorDC motorLeft(pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);

Gyro *giroscopio = new Gyro();

float soma = 0;
float error[2];
long powerRightL = 70;
unsigned long tPrint;
int x, y, z;

void inc()
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
    Wire.begin();

    // Inicializa o HMC5883
    Wire.beginTransmission(address);
    // Seleciona o modo
    Wire.write(0x02);
    // Modo de medicao continuo
    Wire.write(0x00);
    Wire.endTransmission();

    attachInterrupt(digitalPinToInterrupt(19), inc, RISING); // VERIFICAR
    attachInterrupt(digitalPinToInterrupt(18), incR, RISING);
    error[0] = 0;
    error[1] = millis();

    delay(2000);
    tPrint = millis();
}

void loop()
{
    // Delay para começar
    if (firstReading)
    {
        firstReading = false;
        delay(6000);
    }
    ForwardCm(80, 200, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
    int rightEncoderReading = motorRight.getCount();
    int leftEncoderReading = motorLeft.getCount();
    Serial.print("Right Encoder: ");
    Serial.println(rightEncoderReading);
    Serial.print("Left Encoder: ");
    Serial.println(leftEncoderReading);
    delay(1000);
}
