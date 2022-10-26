#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>

Ultrasonic ultrasonic1(US1Trigger, US1Echo);
Ultrasonic ultrasonic2(US2Trigger, US2Echo);
Ultrasonic ultrasonic3(US3Trigger, US3Echo);
Ultrasonic ultrasonic4(US4Trigger, US4Echo);

MotorDC motorRight (pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1); 
MotorDC motorLeft (pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);
void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // Le as informacoes do sensor, em cm e pol
    float cm2Msec;
    float cm3Msec;
    float cm4Msec;

    
    long microsec2 = ultrasonic2.timing();
    cm2Msec = ultrasonic2.convert(microsec2, Ultrasonic::CM);
 
    long microsec3 = ultrasonic3.timing();
    cm3Msec = ultrasonic3.convert(microsec3, Ultrasonic::CM);
 
    long microsec4 = ultrasonic4.timing();
    cm4Msec = ultrasonic4.convert(microsec4, Ultrasonic::CM);
 
    
    Serial.print("\tUS2 cm: ");
    Serial.print(cm2Msec);
    
    Serial.print("\tUS3 cm: ");
    Serial.print(cm3Msec);
    
    Serial.print("\tUS4 cm: ");
    Serial.print(cm4Msec);
    
    Serial.println(); 
    if(cm3Msec < 40 || cm2Msec < 40 ||cm4Msec < 40 ) {
      // moveAll(40, &motorLeft, &motorRight);
      // delay(100);
      stopAll(&motorLeft, &motorRight);
    } else {
      moveRevAll(40, &motorLeft, &motorRight);
    }
    

    delay(500);
}
