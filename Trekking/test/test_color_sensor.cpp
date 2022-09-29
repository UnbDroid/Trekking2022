#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>

// Motor Direita
#define pin1A 3
#define pin1B 7
#define pin1pwm 8
#define pin1Enc A0

// Motor Esquerda
#define pin2A 6
#define pin2B 2
#define pin2pwm 9
#define pin2Enc A1

#define pinEnable1 14
#define pinEnable2 15

//Ultrassom Frente
#define pinFrontTrigger 52
#define pinFrontEcho 53

//Ultrassom Esquerda
#define pinLeftTrigger 50
#define pinLeftEcho 51

//Ultrassom Direita
#define pinRightTrigger 48
#define pinRightEcho 49

// Sensor de cor
#define pinColorS0 22
#define pinColorS1 23
#define pinColorS2 24
#define pinColorS3 25
#define pinColorOut 27

#define EIXO_X 0
#define EIXO_Y 1
#define EIXO_Z 2

int firstReading = true;
int count = 0;
int valueRef;

MotorDC motorRight (5, 7, 8, 18, 14); 
MotorDC motorLeft (6, 4, 9, 2, 15);

Gyro *giroscopio = new Gyro();

ColorSensor *colorSensor = new ColorSensor(pinColorS0, pinColorS1, pinColorS2, pinColorS3, pinColorOut);

float soma = 0;
float error [2];
long powerRightL = 70;
unsigned long tPrint;
int x,y,z;

void inc (){
    motorLeft.encSignal();
  
}

void incR (){
    motorRight.encSignal();
}

void setup() {
    Serial.begin(9600);
    Wire.begin();

    // Inicializa o HMC5883
    Wire.beginTransmission(address);
    // Seleciona o modo
    Wire.write(0x02); 
    // Modo de medicao continuo
    Wire.write(0x00); 
    Wire.endTransmission();

    attachInterrupt(digitalPinToInterrupt(2), inc, RISING);//VERIFICAR 
    attachInterrupt(digitalPinToInterrupt(18), incR, RISING);
    error[0] = 0;
    error[1] = millis();

    delay(2000);
    tPrint = millis();
}

void loop() {
    // Delay para começar
    if (firstReading){
    firstReading = false;
    delay(6000);
    }
    colorSensor->readColor();
    Serial.print("Cor lida: ");
    Serial.println(colorSensor->currentColor);
    delay(1000);
}

