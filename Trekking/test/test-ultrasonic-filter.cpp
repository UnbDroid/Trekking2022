#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <UltrasonicFilter.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>

Ultrasonic ultrasonic1(US1Trigger, US1Echo);
Ultrasonic ultrasonic2(US2Trigger, US2Echo);
Ultrasonic ultrasonic3(US3Trigger, US3Echo);
Ultrasonic ultrasonic4(US4Trigger, US4Echo);

UltrasonicFilter ultrasonicFilter1;
UltrasonicFilter ultrasonicFilter2;
UltrasonicFilter ultrasonicFilter3;
UltrasonicFilter ultrasonicFilter4;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    ultrasonicFilter1.filter(ultrasonic1);
    // ultrassonicFilter(ultrasonic2, results2);
    // ultrassonicFilter(ultrasonic3, results3);
    // ultrassonicFilter(ultrasonic4, results4);

    Serial.print("US1 cm: ");
    ultrasonicFilter1.printArray(ultrasonicFilter1.results);
    
    // Serial.print("US2 cm: ");
    // printArray(results2, 3);
    
    // Serial.print("US3 cm: ");
    // printArray(results3, 3);
    
    // Serial.print("US4 cm: ");
    // printArray(results4, 3);
    
    Serial.println();

    // delay(500);
}
