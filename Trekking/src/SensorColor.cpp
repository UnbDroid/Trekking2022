// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCAO ANTIGA QUE PEGAMOS DO GIT, NAO SEI SE FUNCIONA!!!!!!!!!!!!!!
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <Arduino.h>
#include <SensorColor.h>

SensorColor::SensorColor(int pinColorS0, int pinColorS1, int pinColorS2, int pinColorS3, int pinColorOut) {
    this->pinColorS0 = pinColorS0;
    this->pinColorS1 = pinColorS1;
    this->pinColorS2 = pinColorS2;
    this->pinColorS3 = pinColorS3;
    this->pinColorOut = pinColorOut;

    pinMode(pinColorS0, OUTPUT); // Pino S0 configurado como saida
    pinMode(pinColorS1, OUTPUT); // Pino S1 configurado como saida
    pinMode(pinColorS2, OUTPUT); // Pino S2 configurado como saida
    pinMode(pinColorS3, OUTPUT); // Pino S3 configurado como saida
    pinMode(pinColorOut, INPUT); // Pino OUT configurado como entrada

    digitalWrite(pinColorS0,HIGH); // Inicia o codigo com o pino S0 em nivel alto
    digitalWrite(pinColorS1,LOW); // Inicia o codigo com o pino S1 em nivel baixo
}

void SensorColor::readColors() {
    digitalWrite(pinColorS2, LOW); // Pino S2 em nivel baixo
    digitalWrite(pinColorS3, LOW); // Pino S3 em nivel baixo

    if(digitalRead(pinColorOut) == HIGH){ // Verifica o nivel logico no pino OUT do sensor
        vermelho = pulseIn(pinColorOut, LOW); // Le duracao do pulso na saida
    } else {
        vermelho = pulseIn(pinColorOut, HIGH); // Le duracao do pulso na saida
    }
        
    digitalWrite(pinColorS3, HIGH); // PINO S3 em nivel alto

    if(digitalRead(pinColorOut) == HIGH){ // Verifica o nivel logico no pino OUT do sensor
        azul = pulseIn(pinColorOut, LOW); // Le duracao do pulso na saida
    } else {
        azul = pulseIn(pinColorOut, HIGH); // Le duracao do pulso na saida
    }
        
    digitalWrite(pinColorS2, HIGH); // Pino S2 em nivel alto

    if(digitalRead(pinColorOut) == HIGH){ // Verifica o nivel logico no pino OUT do sensor
        verde = pulseIn(pinColorOut, LOW); // Le duracao do pulso na saida
    } else {
        verde = pulseIn(pinColorOut, HIGH); // Le duracao do pulso na saida
    } 
}