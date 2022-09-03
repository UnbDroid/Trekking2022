#include <Arduino.h>
#include <MotorDC.h>
#include <SensorColor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <ColorSensor.h>
#include <string.h>
#include <defines.h>

int firstReading = true;
int count = 0;
int valueRef;

MotorDC motorRight (5, 7, 8, 18, 14); 
MotorDC motorLeft (6, 4, 9, 2, 15);

Gyro *giroscopio = new Gyro();

ColorSensor *colorSensor = new ColorSensor(pinColorS0, pinColorS1, pinColorS2, pinColorS3, pinColorOut);

float soma = 0;
float error [2];
float giro = 0;
float mR;
float mL;
float pi = 3.14159265;
unsigned long tsart;
long powerRightL = 70;
long teste[6];
int testIndex = 0;
long medTeste;
unsigned long tPrint;
int x,y,z;

int ps_final;

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
    
    attachInterrupt(digitalPinToInterrupt(2), inc, RISING);//VERIFICAR 
    attachInterrupt(digitalPinToInterrupt(18), incR, RISING);
    error[0] = 0;
    error[1] = millis();

    delay(2000);
    tPrint = millis();
}




void gyroTest() {
  double gyroValue = giroscopio->requestData();
  // -----------------------------------------------------------------
  // TESTE GIROSCOPIO
  Serial.print("gyroValue: ");
  Serial.println(gyroValue);
  // Serial.println(giroscopio->requestData());
  // Serial.print("  x: ");
  // Serial.print(x);
  // Serial.print("  y: ");
  // Serial.println(y);
  // -----------------------------------------------------------------
}

void commentedTest() {
  // -----------------------------------------------------------------
  // TESTE SENSOR DE COR
  // colorSensor->readColor();
  // Serial.println(colorSensor->currentColor);
  // delay(1000);
  // -----------------------------------------------------------------


  // if (firstReading)
  // {
  //     valueRef = gyroValue;
  //     firstReading = false;
      
  //     ps_final = fabs(valueRef)+90;//ValueRef + a quantidade de Graus desejada 
  //     //Na função deverá pegar o sentido de giro HORARIO OU ANTI  
  
  //     if (fabs(ps_final) > 180)
  //     {
  //       ps_final -= 180;
  //       //Adicionar condicionais;
  //       ps_final = -180-ps_final;//Se sentido Horario (DIR-0) 
  //       ps_final = 180-ps_final;//Se sentido ANTIHorario (ESQ-1) 

  //       Serial.print("Entrei no IF: ");
  //       Serial.println(ps_final);
  //     }

  //     delay(3000);
  // }
  // //Verificação de Ida
  // //Se valueRef > 0 e DIR = 0 fazer verificação quando >= 179 graus e retirar a diferença restante calculando em
  // //cima de -180
  // //Verificação de Volta
  // //Se ValueRef > 0 e DIR = 1 fazer verificação quando ficar menor que 0, retirar a diferença e somar valor (NEGATIVO) a 0
  // //Atentar se valor passar de -180 para positivo

  // while (gyroValue > ps_final and gyroValue < ps_final+10)//Checar se intervalo de 10 angulos é válido
  // {
  //   Serial.print("TESTE DE SAIDA");
  // }
  
  // Delay para começar
  // if (firstReading){
  //   firstReading = false;
  //   delay(6000);
  // }

  
  // moveAllpidGyro(80, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, 80);
  // turnDegreesGyro2(75,150, ANTIHORARIO, &motorLeft, &motorRight, giroscopio);
  // valueRef = giroscopio->requestData();
  // // while (true){
  //   moveAllpidGyro(80, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
  // }
  // FowardCm(80, 200, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
  // delay(500);
  // turnDegrees(100, 90, ANTIHORARIO, &motorLeft, &motorRight);
  // TIRAR O DELAY SE FOR TESTAR O CONTROLE PID
  // delay(10000);

}

void loop() {
    moveAll(120, &motorLeft, &motorRight);
    // gyroTest();
    // commentedTest();
}