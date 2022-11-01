#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>

#define ESQUERDA 0
#define DIREITA 1

int firstReading = true;
int count = 0;
int valueRef;

MotorDC motorRight(pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);
MotorDC motorLeft(pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1);

Gyro *giroscopio = new Gyro();

float soma = 0;
float error[2];
long powerRightL = 50;
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
double gyroTest()
{
  double gyroValue = giroscopio->requestData();
  // -----------------------------------------------------------------
  Serial.print("gyroValue: ");
  Serial.println(gyroValue);
  return gyroValue;
}

double anguloFinal(int sentido, double valRef, double anguloDesejado)
{
  double anguloFinal = 0;
  if (sentido == ESQUERDA)
  {
    anguloFinal = valRef + anguloDesejado;
    if (anguloFinal > 360)
    {
      anguloFinal -= 360;
    }
  }
  else
  {
    anguloFinal = valRef - anguloDesejado;
    if (anguloFinal < 0)
    {
      anguloFinal += 360;
    }
  }
  return anguloFinal;
}

void loop()
{

  // firstReading = false;
  // Delay para começar

  if (firstReading)
  {
    valueRef = giroscopio->requestData();
    Serial.print("valueRef: ");
    Serial.println(valueRef);
    delay(2000);
    motorLeft.rev(100);
    motorRight.fwd(100);
    double anguloF = anguloFinal(DIREITA, valueRef, 90);
    Serial.print("AnguloDesejado = ");
    Serial.println(anguloF);
    while (giroscopio->requestData() < anguloF)
    {
      double gyroValue = gyroTest();
      Serial.print("AnguloDesejado = ");
      Serial.println(anguloF);

      delay(1000);
    }
    stopAll(&motorLeft, &motorRight);

    //   turnDegreesGyro2(100, 90, HORARIO, &motorLeft, &motorRight, giroscopio);
    // turnDegrees(60, 90, HORARIO, &motorLeft, &motorRight);
    firstReading = false;
  }
  delay(100);
  // stopAll(&motorLeft, &motorRight);
}
