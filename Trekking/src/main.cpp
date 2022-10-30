#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>

void setup()
{
    Serial.begin(9600);

    pinMode(14, INPUT);
    pinMode(15, INPUT);
    pinMode(16, INPUT);
    pinMode(17, INPUT);
    pinMode(26, INPUT);
    pinMode(28, INPUT);
    pinMode(34, INPUT);
}


void loop() 
{


    // Delay para começar

    uint8_t res = 0xb0000000;
    while(true)
    {
        Serial.print(digitalRead(14));
        Serial.print(digitalRead(15));
        Serial.print(digitalRead(16));
        Serial.print(digitalRead(17));
        Serial.print(digitalRead(26));
        Serial.print(digitalRead(28));
        Serial.print(digitalRead(34));

        res = (digitalRead(14)) | (digitalRead(15) << 1) | (digitalRead(16) << 2) | (digitalRead(17) << 3) | (digitalRead(26) << 4) | (digitalRead(28) << 5) | ((digitalRead(34) << 6));
        Serial.println(res);
        delay(1000);
    }
   
}
