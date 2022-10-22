
#include <Arduino.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <string.h>
#include <defines.h>

Gyro *giroscopio = new Gyro();

void setup() {
    Serial.begin(9600);
    pinMode(14, INPUT);
    pinMode(15, INPUT);
    pinMode(16, INPUT);
    pinMode(17, INPUT);
}


void loop() {
    uint8_t bits[4];
    bits[0] = digitalRead(14);
    bits[1] = digitalRead(15);
    bits[2] = digitalRead(16);
    bits[3] = digitalRead(17);
    int decValue = bits[0] + (bits[1] * 2) + (bits[2]*2*2) + (bits[3]*2*2*2); 

    Serial.print("Angulo do Cone = ");
    Serial.println(decValue);



}