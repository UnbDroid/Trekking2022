#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <UltrasonicFilter.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>

Ultrasonic ultrasonic2(US2Trigger, US2Echo);
Ultrasonic ultrasonic3(US3Trigger, US3Echo);
Ultrasonic ultrasonic4(US4Trigger, US4Echo);

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    float *filtered_values;

    filtered_values = filter(ultrasonic2, ultrasonic3, ultrasonic4);

    Serial.print("US2 cm: ");
    Serial.print(filtered_values[0]);

    Serial.print("\tUS3 cm: ");
    Serial.print(filtered_values[1]);

    Serial.print("\tUS4 cm: ");
    Serial.print(filtered_values[2]);

    Serial.println();

    // delay(500);
}
