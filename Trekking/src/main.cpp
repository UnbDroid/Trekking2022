#include <Arduino.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <string.h>
#include <defines.h>

Gyro *giroscopio = new Gyro();

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
    pinMode(SinalLuminoso, OUTPUT);
    digitalWrite(SinalLuminoso, LOW);
}

void gyroTest() {
  double gyroValue = giroscopio->requestData();
  // -----------------------------------------------------------------
  Serial.print("gyroValue: ");
  Serial.println(gyroValue);
  // -----------------------------------------------------------------
}

void loop() {
    digitalWrite(SinalLuminoso, HIGH);
    delay(500);
    digitalWrite(SinalLuminoso, LOW);
    delay(500);

    
    gyroTest();
    gyroTest();
}