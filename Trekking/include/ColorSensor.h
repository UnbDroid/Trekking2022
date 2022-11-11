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
    int limiarRGB_Yellow[3] = {28, 43, 48};
    int limiarRGB_Green[3] = {112, 78, 86};
    int limiarRGB_Red[3] = {33, 84, 66};

    ColorSensor(int ColorSensorS0, int ColorSensorS1, int ColorSensorS2, int ColorSensorS3, int ColorSensorOut);

    ~ColorSensor();

    void readColor();
    void findNearest();
    void calibrate();
    void readCalibration();
    int getAverageNReadings(int N, int color);

private:
    int ColorSensorS0;
    int ColorSensorS1;
    int ColorSensorS2;
    int ColorSensorS3;
    int ColorSensorOut;

    void writeCalibrationOnEPPROM();
    void fetchCalibrationFromEPPROM();
};

#endif