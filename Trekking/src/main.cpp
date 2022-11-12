// Programa : Teste HMC5883L - Bussola
// Adaptacoes : Arduino e Cia

#include <Wire.h>
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
long powerRightL = 70;
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
}

void loop() 
{
    // Delay para começar
    if (firstReading)
    {
        firstReading = false;
        delay(1000);
    }

    moveAll(potencia, &motorLeft, &motorRight);
    delay(1000);
    stopAll(&motorLeft, &motorRight);

    Serial.println("\n\nStopped moving\n\n");

    rightEncoderReading = motorRight.getCount();
    leftEncoderReading = motorLeft.getCount();

    Serial.print("Right Encoder: ");
    Serial.println(rightEncoderReading);
    Serial.print("Left Encoder: ");
    Serial.println(leftEncoderReading);
    delay(1000);
}