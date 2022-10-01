#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>


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
    
    pinMode(13, OUTPUT);
    pinMode(pinColorS0, OUTPUT);
    pinMode(pinColorS1, OUTPUT);
    pinMode(pinColorS2, OUTPUT);
    pinMode(pinColorS3, OUTPUT);
    pinMode(pinColorOut, INPUT);

    delay(2000);
    tPrint = millis();
}

void loop() {
    // digitalWrite(13, HIGH);  
    // delay(500); 
    // digitalWrite(13, LOW);
    // delay(500);

    
    digitalWrite(pinColorS0, HIGH);
    digitalWrite(pinColorS1, HIGH);
    digitalWrite(pinColorS2, HIGH);
    digitalWrite(pinColorS3, LOW);

    int redFrequency = pulseIn(pinColorOut, LOW);
  
   // Printing the RED (R) value
    Serial.print("R = ");
    Serial.print(redFrequency);
    delay(100);

}
