#include <Arduino.h>
#include "MPU9250.h"
#include <MotorDC.h>
#include <SensorColor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>

// Motor Direita
#define pin1A 5
#define pin1B 6
#define pin1pwm 7
#define pin1Enc A0

// Motor Esquerda
#define pin2A 8
#define pin2B 9
#define pin2pwm 10
#define pin2Enc A1

//Ultrassom Frente
#define pinFrontTrigger 52
#define pinFrontEcho 53

//Ultrassom Esquerda
#define pinLeftTrigger 50
#define pinLeftEcho 51

//Ultrassom Direita
#define pinRightTrigger 48
#define pinRightEcho 49

// Sensor de cor esquerda
#define pinColorLeftS0 44
#define pinColorLeftS1 45
#define pinColorLeftS2 46
#define pinColorLeftS3 47
#define pinColorLeftOut 43


#define EIXO_X 0
#define EIXO_Y 1
#define EIXO_Z 2

int firstReading = true;
int count = 0;
int valueRefer;

MotorDC motorRight (5, 7, 8, 18); 
MotorDC motorLeft (6, 4, 9, 2);

MPU9250 mpu;

float soma = 0;
float error [2];
float giro = 0;
float mR;
float mL;
unsigned long tsart;
long powerRightL = 60;
long teste[6];
int testIndex = 0;
long medTeste;
unsigned long tPrint;

void print_roll_pitch_yaw() {
    Serial.print("Yaw, Pitch, Roll: ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print(", ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(", ");
    Serial.print(mpu.getRoll(), 2);
    Serial.print("  ");
    Serial.print("Mag : ");
    Serial.print(mpu.getMagX(), 2);
    Serial.print(", ");
    Serial.print(mpu.getMagY(), 2);
    Serial.print(", ");
    Serial.print(mpu.getMagZ(), 2);
    Serial.print(", ");
    Serial.print("lin_acc = ");
    Serial.print(mpu.getLinearAccX(), 2);
    Serial.print(", ");
    Serial.print(mpu.getLinearAccY(), 2);
    Serial.print(", ");
    Serial.println(mpu.getLinearAccZ(), 2);
}

void print_calibration() {
    Serial.println("< calibration parameters >");
    Serial.println("accel bias [g]: ");
    Serial.print(mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY);
    Serial.println();
    Serial.println("gyro bias [deg/s]: ");
    Serial.print(mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.print(", ");
    Serial.print(mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY);
    Serial.println();
    Serial.println("mag bias [mG]: ");
    Serial.print(mpu.getMagBiasX());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasY());
    Serial.print(", ");
    Serial.print(mpu.getMagBiasZ());
    Serial.println();
    Serial.println("mag scale []: ");
    Serial.print(mpu.getMagScaleX());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleY());
    Serial.print(", ");
    Serial.print(mpu.getMagScaleZ());
    Serial.println();
}

void inc (){

  motorLeft.encSignal();
  
}

void incR (){

	motorRight.encSignal();
}


void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(2000);
    tPrint = millis();

    if (!mpu.setup(0x68)) {  // change to your own address
        while (1) {
            Serial.println("MPU connection failed. Please check your connection with `connection_check` example.");
            delay(5000);
        }
    }

    // // calibrate anytime you want to
    // Serial.println("Accel Gyro calibration will start in 5sec.");
    // Serial.println("Please leave the device still on the flat plane.");
    // mpu.verbose(true);
    // delay(5000);
    // mpu.calibrateAccelGyro();

    // Serial.println("Mag calibration will start in 5sec.");
    // Serial.println("Please Wave device in a figure eight until done.");
    // delay(5000);
    // mpu.calibrateMag();

    // print_calibration();
    // mpu.verbose(false);
}

void loop() {
    if (mpu.update()) {
        static uint32_t prev_ms = millis();
        if (millis() > prev_ms + 25) {
            //print_roll_pitch_yaw();
            
            teste[testIndex] = mpu.getYaw();
            testIndex = (testIndex == 4) ? 0 : testIndex+1;
            prev_ms = millis();
        }
    }
    //Serial.println(teste[0]);
    //Serial.println(mpu.getEulerX());
    //Serial.println(mpu.getEulerY());
    //Serial.println(mpu.getEulerZ());
    //Serial.println(mpu.getEulerZ());
    if(millis() - tPrint > 500) {
      tPrint = millis();
      //print_calibration();
      Serial.println(mpu.getMagY());

      // Serial.println();
      // Serial.println("LEFT");
      // Serial.println(powerLeft);
      // Serial.println("right");
      // Serial.println(powerRight);
      }
    
    //Serial.println();   
   
    // delay(1000);
    // if (count > 1000 )
    // {
    //     if (firstReading)
    //     {
    //         //valueRefer = teste;
    //         firstReading = false;
    //     }
    //     for (size_t i = 0; i < 3; ++i) {
    //         medTeste += teste[i];
    //     }
    //     medTeste = medTeste / 3;
    //     moveAllpidGyro(50, &motorLeft, &motorRight, &soma, error, medTeste, &powerRightL, valueRefer, &tPrint);

    // }else
    // {
    //     count += 1;
    // }

}

