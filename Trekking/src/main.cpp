#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <UltrasonicFilter.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>
#include <VisionSensor.h>


int firstReading = 1;
int count = 0;
float valueRef;

MotorDC motorRight(pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);
MotorDC motorLeft(pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1);

Gyro *giroscopio = new Gyro();

VisionSensor camera(VISION_START);


float soma = 0;
float error[2];
long powerRightL = 100;
unsigned long tPrint;
int x, y, z;

int potencia = 100;
int distanciaCm = 200;
int rightEncoderReading = motorRight.getCount();
int leftEncoderReading = motorLeft.getCount();
int cameraResult = 180;
long firstTime;


Ultrasonic ultrasonic2(US2Trigger, US2Echo);
Ultrasonic ultrasonic3(US3Trigger, US3Echo);
Ultrasonic ultrasonic4(US4Trigger, US4Echo);

ColorSensor corSen(ColorSensorS0, ColorSensorS1, ColorSensorS2, ColorSensorS3, ColorSensorOut);

float *filtered_values;


void incL()
{
    motorLeft.encSignal();
}

void incR()
{
    motorRight.encSignal();
}

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

    uint8_t pin1Interrupt = digitalPinToInterrupt(pin1Enc);
    uint8_t pin2Interrupt = digitalPinToInterrupt(pin2Enc);

    attachInterrupt(pin1Interrupt, incR, RISING); // VERIFICAR
    attachInterrupt(pin2Interrupt, incL, RISING);
    error[0] = 0;
    error[1] = millis();

    pinMode(SinalLuminoso, OUTPUT);
    digitalWrite(SinalLuminoso, LOW);


    delay(2000);
    tPrint = millis();
}

void firstPart(){

  while (true){
    if (firstReading)
      {
        for (size_t i = 0; i < 20; i++)
        {
          valueRef += giroscopio->requestData();
        }
          valueRef = valueRef/20;
          moveAllpidGyroNew(100, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
        
          // delay(1000);
          
          Serial.print("valueRef: ");
          Serial.println(valueRef);
          firstTime = millis();

          // delay(3000);
          // ForwardCm(100, 700, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
          firstReading = false;
      }

      float *filtered_values;

      // if(millis() - firstTime > 4000){
      //   cameraResult = camera.getFilteredAngle();
      // }

      // if(cameraResult < 170)
      // {
      //   moveAllpidVision(100, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, 90);
      // }

      filtered_values = filter(ultrasonic2, ultrasonic3, ultrasonic4);
      
      if(filtered_values[1] < 45 || filtered_values[0] < 45 ||filtered_values[2] < 45 ) {
        // moveAll(40, &motorLeft, &motorRight);
        digitalWrite(SinalLuminoso, HIGH);
        stopAll(&motorLeft, &motorRight);
        delay(2000);
        digitalWrite(SinalLuminoso, LOW);
        moveRevAll(potencia, &motorLeft, &motorRight);
        delay(500);
        stopAll(&motorLeft, &motorRight);
        turnToDesiredAngleGyro(120, -105, &motorLeft, &motorRight, giroscopio);
        delay(2000);
        return;

        // turnAnticlockwise(100,&motorLeft,&motorRight);
        // Serial.print("PAREEEEEEEEEEEEEEEEEEEEI");
      } else {
        // Serial.print("GOOOOOOOOOOOOOOOOOOOOOOO");
        digitalWrite(SinalLuminoso, LOW);
        moveAllpidGyroNew(100, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
      }
  }
}

void loop()
{
    corSen.readColor();

    // Delay para começar
    //firstPart();
    if (firstReading == 1)
      {
        for (size_t i = 0; i < 20; i++)
        {
          valueRef += giroscopio->requestData();
        }
          valueRef = valueRef/20;
          Serial.println(valueRef);
          moveAllpidGyroNew(100, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);

          firstReading = 2;
      }

      if(firstReading == 2)
      {
        filtered_values = filter(ultrasonic2, ultrasonic3, ultrasonic4);
        corSen.readColor();
        if(filtered_values[1] < 70 || filtered_values[0] < 70 ||filtered_values[2] < 70 || (strcmp(corSen.currentColor, "yellow") == 0)) {
        corSen.readColor();
        
          if(strcmp(corSen.currentColor, "yellow") == 0) {
            
            // moveAll(40, &motorLeft, &motorRight);
            digitalWrite(SinalLuminoso, HIGH);
            stopAll(&motorLeft, &motorRight);
            delay(2000);
            digitalWrite(SinalLuminoso, LOW);
            moveRevAll(potencia, &motorLeft, &motorRight);
            delay(500);
            stopAll(&motorLeft, &motorRight);
            turnToDesiredAngleGyro(120, -105, &motorLeft, &motorRight, giroscopio);
            delay(2000);
            firstReading = 3;
          }
          // turnAnticlockwise(100,&motorLeft,&motorRight);
          // Serial.print("PAREEEEEEEEEEEEEEEEEEEEI");
        } else {
          // Serial.print("GOOOOOOOOOOOOOOOOOOOOOOO");
          digitalWrite(SinalLuminoso, LOW);
          moveAllpidGyroNew(110, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
        }
      }

      if(firstReading == 3)
      {
       for (size_t i = 0; i < 20; i++)
        {
          valueRef += giroscopio->requestData();
        }
          valueRef = valueRef/20;
          moveAllpidGyroNew(110, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
        firstReading = 4;
      }


      if(firstReading == 4)
      {
        if(filtered_values[1] < 70 || filtered_values[0] < 70 ||filtered_values[2] < 70 ) {
          stopAll(&motorLeft, &motorRight);
          delay(2000);
          moveRevAll(potencia, &motorLeft, &motorRight);
          delay(500);
          stopAll(&motorLeft, &motorRight);
          turnToDesiredAngleGyro(100, 130, &motorLeft, &motorRight, giroscopio);
          delay(2000);
        }

      }


    // stopAll(&motorLeft, &motorRight);
}
