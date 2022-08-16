// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCAO NOVA QUE FIZEMOS!!!!!!!!!!!!!!
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <Arduino.h>
#include <string>

class ColorSensor
{
    public:

    int red = 0;
    int green = 0;
    int blue = 0;

    ColorSensor(int pinColorS0, int pinColorS1, int pinColorS2, int pinColorS3, int pinColorOut);

    ~ColorSensor();

    string readColor();

    private:

    int pinColorS0;
    int pinColorS1;
    int pinColorS2;
    int pinColorS3;
    int pinColorOut;
};

#endif