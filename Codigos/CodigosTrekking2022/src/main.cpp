#include <Arduino.h>
#include <MotorDC.h>
#include <SensorColor.h>
#include <Ultrasonic.h>

// Motor Direita Frente
#define pin1A 5
#define pin1B 6
#define pin1pwm 7
#define pin1Enc A0

// Motor Direita Tras
#define pin1A 5
#define pin1B 6
#define pin1pwm 7
#define pin1Enc A0

// Motor Esquerda Frente
#define pin2A 8
#define pin2B 9
#define pin2pwm 10
#define pin2Enc A1

// Motor Esquerda Tras
#define pin2A 8
#define pin2B 9
#define pin2pwm 10
#define pin2Enc A1

//Ultrassom
#define pinFrontTrigger 52
#define pinFrontEcho 53

// Sensor de cor
#define pinColorLeftS0 44
#define pinColorLeftS1 45
#define pinColorLeftS2 46
#define pinColorLeftS3 47
#define pinColorLeftOut 43


MotorDC motorRight(pin1A, pin1B, pin1pwm, pin1Enc);
MotorDC motorLeft(pin2A, pin2B, pin2pwm, pin2Enc);

Ultrasonic sensorUltra(pinFrontTrigger, pinFrontEcho);

SensorColor sensorColor(pinColorLeftS0, pinColorLeftS1, pinColorLeftS2, pinColorLeftS3, pinColorLeftOut);


void setup() {
  Serial.begin(9600);

}


void loop() {
  // motorRight.fwd(70);
  // motorLeft.fwd(70);
  // delay(5000);
  // motorRight.stop();
  // motorLeft.stop();
  // delay(5000);
  // motorRight.rev(70);
  // motorLeft.rev(70);
  // delay(5000);

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

  sensorColor.readColors(); // Chama a rotina que le as cores

  // Verifica se a cor vermelha foi detectada
  if (sensorColor.vermelho < sensorColor.azul && sensorColor.vermelho < sensorColor.verde){
    Serial.print("VERMELHO");
    Serial.print("\n");
  }
  
  if (sensorColor.azul < sensorColor.vermelho && sensorColor.azul < sensorColor.verde) { // Verifica se a cor azul foi detectada
    Serial.print("AZUL");
    Serial.print("\n");
  }
  
  if (sensorColor.verde < sensorColor.vermelho && sensorColor.verde < sensorColor.azul) { // Verifica se a cor verde foi detectada
    Serial.print("VERDE");
    Serial.print("\n");
  }

  delay(1000); // Aguarda 1000 milissegundos
}
