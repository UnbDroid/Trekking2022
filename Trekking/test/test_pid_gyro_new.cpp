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

MotorDC motorRight(pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);
MotorDC motorLeft(pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1);

Gyro *giroscopio = new Gyro();

float soma = 0;
float error[2];
long powerRightL = 100;
unsigned long tPrint;
int x, y, z;

int potencia = 40;
int distanciaCm = 200;
int rightEncoderReading = motorRight.getCount();
int leftEncoderReading = motorLeft.getCount();

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

    Wire.begin();
    // Inicializa o HMC5883
    Wire.beginTransmission(address);
    // Seleciona o modo
    Wire.write(0x02);
    // Modo de medicao continuo
    Wire.write(0x00);
    Wire.endTransmission();

    uint8_t pin1Interrupt = digitalPinToInterrupt(pin1Enc);
    uint8_t pin2Interrupt = digitalPinToInterrupt(pin2Enc);

    attachInterrupt(pin1Interrupt, incR, RISING); // VERIFICAR
    attachInterrupt(pin2Interrupt, incL, RISING);
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
        delay(1000);
        valueRef = giroscopio->requestData();
        Serial.print("valueRef: ");
        Serial.println(valueRef);
        delay(3000);
        // ForwardCm(100, 700, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
        firstReading = false;
    }
    moveAllpidGyroNew(150, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
    // stopAll(&motorLeft, &motorRight);
}
