#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>
// #include <StandardCplusplus.h>

Ultrasonic ultrasonic1(US1Trigger, US1Echo);
Ultrasonic ultrasonic2(US2Trigger, US2Echo);
Ultrasonic ultrasonic3(US3Trigger, US3Echo);
Ultrasonic ultrasonic4(US4Trigger, US4Echo);
// #include <algorithm>
// #include <vector>
// std::vector<float> ultrassonicFilter(Ultrasonic ultrassonic)
// {
//   const int NUM_OF_READINGS = 10;
//   const int NUM_OF_SAMPLES = 1;
//   float values[NUM_OF_READINGS];
//   std::vector<float> results;
//   for (int i = 0; i < NUM_OF_READINGS; i++)
//   {
//     long auxValue = ultrassonic.timing();
//     values[i] = ultrassonic.convert(auxValue, Ultrasonic::CM);
//   }
//   std::sort(values, values + NUM_OF_READINGS);
//   for (int i = (NUM_OF_READINGS / 2) - NUM_OF_SAMPLES; i <= (NUM_OF_READINGS / 2) + NUM_OF_SAMPLES; i++)
//   {
//     results.push_back(values[i]);
//   }
//   return results;
// }

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // Le as informacoes do sensor, em cm e pol
    float cm1Msec;
    float cm2Msec;
    float cm3Msec;
    float cm4Msec;

    long microsec1 = ultrasonic1.timing();
    cm1Msec = ultrasonic1.convert(microsec1, Ultrasonic::CM);
 
    long microsec2 = ultrasonic2.timing();
    cm2Msec = ultrasonic2.convert(microsec2, Ultrasonic::CM);
 
    long microsec3 = ultrasonic3.timing();
    cm3Msec = ultrasonic3.convert(microsec3, Ultrasonic::CM);
 
    long microsec4 = ultrasonic4.timing();
    cm4Msec = ultrasonic4.convert(microsec4, Ultrasonic::CM);
 

    // Exibe informacoes no serial monitor
    Serial.print("US1 cm: ");
    Serial.print(cm1Msec);
    
    Serial.print("\tUS2 cm: ");
    Serial.print(cm2Msec);
    
    Serial.print("\tUS3 cm: ");
    Serial.print(cm3Msec);
    
    Serial.print("\tUS4 cm: ");
    Serial.print(cm4Msec);
    
    Serial.println();

    delay(500);
}
