#include <Arduino.h>
#include <MotorDC.h>
#include <SensorColor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>

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

#define address 0x1E 
#define EIXO_X 0
#define EIXO_Y 1
#define EIXO_Z 2

int firstReading = true;
int count = 0;
int valueRefer;

MotorDC motorRight (5, 7, 8, 18); 
MotorDC motorLeft (6, 4, 9, 2);

float soma = 0;
float error [2];
float giro = 0;
float mR;
float mL;
float pi = 3.14159265;
unsigned long tsart;
long powerRightL = 60;
long teste[6];
int testIndex = 0;
long medTeste;
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
  
    delay(2000);
    tPrint = millis();
}

void loop() {

  // Indica ao HMC5883 para iniciar a leitura
  Wire.beginTransmission(address);
  Wire.write(0x03); //select register 3, X MSB register
  Wire.endTransmission();
 
  // Le os dados de cada eixo, 2 registradores por eixo
  Wire.requestFrom(address, 6);
  if(6<=Wire.available())
  {
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
  }

  double result = atan2(y,x);

  double degree = result *(360/3.141592); 
    
  
  // Imprime os vaores no serial monitor
  Serial.print("Degree: ");
  Serial.print(degree);
  // Serial.print("  result: ");
  // Serial.println(result);
  // Serial.print("  z: ");
  // Serial.println(z);
  

  delay(250);
    // delay(1000);
    // if (count > 200 )
    // {
    // //     if (firstReading)
    // //     {
    // //         //valueRefer = teste;
    // //         firstReading = false;
    // //     }
    // //     for (size_t i = 0; i < 3; ++i) {
    // //         medTeste += teste[i];
    // //     }
    // //     medTeste = medTeste / 3;
    //     // moveAllpidGyro(50, &motorLeft, &motorRight, &soma, error, x, &powerRightL, valueRefer, &tPrint);

    // }else
    // {
    //     count += 1;
    // }

}

