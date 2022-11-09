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

    ColorSensor(int ColorSensorS0, int ColorSensorS1, int ColorSensorS2, int ColorSensorS3, int ColorSensorOut);

    ~ColorSensor();

    void readColor();

private:
    int ColorSensorS0;
    int ColorSensorS1;
    int ColorSensorS2;
    int ColorSensorS3;
    int ColorSensorOut;
};

#endif