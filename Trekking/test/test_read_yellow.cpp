#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>
#include <string.h>

int firstReading = true;

int count = 0;
int valueRef;

float soma = 0;
float error [2];
float giro = 0;
float mR;
float mL;
float pi = 3.14159265;
unsigned long tsart;
long powerRightL = 70;
long teste[6];
int testIndex = 0;
long medTeste;
unsigned long tPrint;
int x,y,z;

int ps_final;

MotorDC motorRight (pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1); 
MotorDC motorLeft (pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);


void inc (){
  motorLeft.encSignal();
  
}

void incR (){
	motorRight.encSignal();
}

ColorSensor *colorSensor = new ColorSensor(ColorSensorS0, ColorSensorS1, ColorSensorS2, ColorSensorS3, ColorSensorOut);
Gyro *giroscopio = new Gyro();

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

    attachInterrupt(digitalPinToInterrupt(2), inc, RISING); // VERIFICAR
    attachInterrupt(digitalPinToInterrupt(18), incR, RISING);
    
    pinMode(SinalLuminoso, OUTPUT);
    digitalWrite(SinalLuminoso, LOW);

    error[0] = 0;
    error[1] = millis();

}

void loop()
{
  colorSensor->readColor();
  Serial.print("Cor lida: ");
  Serial.println(colorSensor->currentColor);
  if (strcmp(colorSensor->currentColor, "yellow") == 0)
  {
    stopAll(&motorLeft, &motorRight);
    digitalWrite(SinalLuminoso, HIGH);
    delay(500);
    digitalWrite(SinalLuminoso, LOW);
    delay(500);
  }

    colorSensor->readColor();
    moveAll(60, &motorLeft, &motorRight);
}