#include <Arduino.h>
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


#define EIXO_X 4
#define EIXO_Y 5
#define EIXO_Z 6


MotorDC motorRight (5, 7, 8, 18); 
MotorDC motorLeft (6, 4, 9, 2);

Ultrasonic SensorUltraFront(pinFrontTrigger, pinFrontEcho);
Ultrasonic SensorUltraLeft(pinLeftTrigger, pinLeftEcho);
Ultrasonic SensorUltraRight(pinRightTrigger, pinRightEcho);

SensorColor SensorColorLeft(pinColorLeftS0, pinColorLeftS1, pinColorLeftS2, pinColorLeftS3, pinColorLeftOut);

Gyro gyroscope;

//Declaração de variáveis que serão parâmetros na função moveAllpid.
float soma = 0;
float error [2];
float giro = 0;
float mR;
float mL;
unsigned long tsart;
long powerRightL = 60;

void inc (){

  motorLeft.encSignal();
  
}

void incR (){

	motorRight.encSignal();
}

void setup() {
	tsart = millis();
  	Serial.begin(9600);
  	attachInterrupt(digitalPinToInterrupt(2), inc, RISING);
	attachInterrupt(digitalPinToInterrupt(18), incR, RISING);
  	error[0] = 0;
	error[1] = millis();
	Wire.begin();
    Wire.beginTransmission(0x68);  //Inicia transmissão para o endereço do MPU
    Wire.write(0x6B);
    Wire.write(0); 
    Wire.endTransmission(true);
}


void loop() {



	long angular = ((gyroscope.filter(10, EIXO_Z)));
// 	Serial.print("eixo z:");
// 	Serial.print(angular);
// 	Serial.print("\n");
	delay(500); 

  
  while(millis()- tsart < 5000){

  }
	// turnDegrees(60, 90, HORARIO, &motorLeft, &motorRight);
  	// FowardCm(80, 1800, &motorLeft, &motorRight, &soma, error, angular, &powerRightL);
  	moveAllpidGyro(80, &motorLeft, &motorRight, &soma, error, angular, &powerRightL);
	
	Serial.print("Esquerda: ");
	Serial.println(motorLeft.getCount());
	Serial.print("Direita: ");
	Serial.println(motorRight.getCount());

  
}