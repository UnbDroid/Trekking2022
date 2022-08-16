// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCAO NOVA QUE FIZEMOS!!!!!!!!!!!!!!
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <Arduino.h>
#include <ColorSensor.h>
#include <string>

ColorSensor::ColorSensor(int pinColorS0, int pinColorS1, int pinColorS2, int pinColorS3, int pinColorOut)
{
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
}

string ColorSensor::readColor()
{

}