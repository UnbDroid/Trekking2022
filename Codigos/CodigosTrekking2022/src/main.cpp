#include <Arduino.h>
#include <MotorDC.h>
#include <SensorColor.h>
#include <Ultrasonic.h>
#include <Move.h>

// Motor Direita
#define pin1A 5
#define pin1B 7
#define pin1pwm 8
#define pin1Enc 18

// Motor Esquerda
#define pin2A 6
#define pin2B 4
#define pin2pwm 9
#define pin2Enc 19

//Ultrassom
// #define pinTrigger 52
// #define pinEcho 53

// Sensor de cor
// #define pinColorS0 44
// #define pinColorS1 45
// #define pinColorS2 46
// #define pinColorS3 47
// #define pinColorOut 43


MotorDC motorRight(pin1A, pin1B, pin1pwm, pin1Enc);
MotorDC motorLeft(pin2A, pin2B, pin2pwm, pin2Enc);

// Ultrasonic sensorUltra(pinTrigger, pinEcho);

// SensorColor sensorColor(pinColorS0, pinColorS1, pinColorS2, pinColorS3, pinColorOut);

void inc (){

  motorLeft.encSignal();
  
}

void incR (){

	motorRight.encSignal();
  Serial.print("Enc 1: ");
  Serial.println(motorRight.getCount());
}


void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(pin1Enc), incR, RISING);
  attachInterrupt(digitalPinToInterrupt(pin2Enc), inc, RISING);
  motorRight.fwd(50);
  motorLeft.fwd(50);
}


void loop() {
  // -------------------------------------------------------------------------------------------------------------
  // Código de teste dos Motores
  
  Serial.print("Enc 2: ");
  Serial.println(motorLeft.getCount());

  // delay(2000);
  // motorRight.stop();
  // motorLeft.stop();
  // delay(2000);
  // motorRight.rev(70);
  // motorLeft.rev(70);
  // delay(2000);
  // motorRight.stop();
  // motorLeft.stop();
  // delay(2000);

  // -------------------------------------------------------------------------------------------------------------
  // Código de teste para o Ultrassom
  //Le as informacoes do sensor, em cm e pol
  // float cmMsecFront, cmMsecLeft, cmMsecRight;
  // long microsecFront = sensorUltra.timing();
  // cmMsecFront = sensorUltra.convert(microsecFront, Ultrasonic::CM);
  // //Exibe informacoes no serial monitor
  // Serial.print("Distancia frente em cm: ");
  // Serial.print(cmMsecFront);
  // Serial.print("\n");
  // Serial.print("\n");
  // delay(1000);


  // -------------------------------------------------------------------------------------------------------------
  // Código de teste para o sensor de Cor
  // sensorColor.readColors(); // Chama a rotina que le as cores

  // // Verifica se a cor vermelha foi detectada
  // if (sensorColor.vermelho < sensorColor.azul && sensorColor.vermelho < sensorColor.verde){
  //   Serial.print("VERMELHO");
  //   Serial.print("\n");
  // }
  
  // if (sensorColor.azul < sensorColor.vermelho && sensorColor.azul < sensorColor.verde) { // Verifica se a cor azul foi detectada
  //   Serial.print("AZUL");
  //   Serial.print("\n");
  // }
  
  // if (sensorColor.verde < sensorColor.vermelho && sensorColor.verde < sensorColor.azul) { // Verifica se a cor verde foi detectada
  //   Serial.print("VERDE");
  //   Serial.print("\n");
  // }

  //delay(1000); // Aguarda 1000 milissegundos
}
