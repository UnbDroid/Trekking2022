// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCAO NOVA QUE FIZEMOS!!!!!!!!!!!!!!
// https://www.usinainfo.com.br/blog/projeto-arduino-sensor-de-cor-verificando-cores-com-tcs230-e-led-rgb/
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef COLORSENSOR_H
#define COLORSENSOR_H

#include <Arduino.h>
#include <string.h>

class ColorSensor
{
    public:

    int red = 0;
    int green = 0;
    int blue = 0;
    char currentColor[7] = "";

    ColorSensor(int pinColorS0, int pinColorS1, int pinColorS2, int pinColorS3, int pinColorOut);

    ~ColorSensor();

    void readColor();

    private:

    int pinColorS0;
    int pinColorS1;
    int pinColorS2;
    int pinColorS3;
    int pinColorOut;
};

#endif