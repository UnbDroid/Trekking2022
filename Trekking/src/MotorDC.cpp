#include <Arduino.h>
#include <MotorDC.h>

//Função do Construtor.
MotorDC::MotorDC(int pinA, int pinB, int pinPwm, int pinEnc, int pinEnable){

    //Setando os atributos da classe com os valores passado pela função.
    this->pinA = pinA;
    this->pinB = pinB; 
    this->pinPwm = pinPwm;
    this->pinEnc = pinEnc;

    //Setando atributos utilizados para monitoramento do encoder
    this->dir = 0;
    this->encCount = 0;

    //Setando os pinos com OUTPUT e o de leitura do encoder com INPUT.
    pinMode(pinA, OUTPUT);
    pinMode(pinB, OUTPUT);
    pinMode(pinPwm, OUTPUT);
    pinMode(pinEnc, INPUT);
    pinMode(pinEnable, OUTPUT);


    digitalWrite(pinEnable, HIGH);
    
}

//Função do Destrutor.
MotorDC::~MotorDC(){}


//Função que anda para frente.
void MotorDC::fwd(int pot){
    int finalPot = pot;
    if(pot > this->maxPot) {
        finalPot = this->maxPot;
        Serial.println("Acima do valor máximo");
    }
    //Sentido de rotação do motor
    dir = 1;

    digitalWrite(pinA, HIGH);
    digitalWrite(pinB, LOW);
    analogWrite(pinPwm, finalPot);

}

//Função que anda para trás.
void MotorDC::rev(int pot){
    int finalPot = pot;
    if(pot > this->maxPot) {
        finalPot = this->maxPot;
    }
    dir = -1;

    digitalWrite(pinA, LOW);
    digitalWrite(pinB, HIGH);
    analogWrite(pinPwm, finalPot);
   
}

//Função de parada.

void MotorDC::stop(){

    dir = 0;

    digitalWrite(pinA, LOW);
    digitalWrite(pinB, LOW);
}

//Função para incrementar contador de pulsos do encoder, de acordo com sentido de rotação do motor.

void MotorDC::encSignal(){

    encCount += dir;

}

long unsigned int MotorDC::getCount(){
    return encCount;
}