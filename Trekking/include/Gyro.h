#ifndef GYRO_H
#define GYRO_H
#include <Wire.h>
#include <Arduino.h>
#define address 0x1E 


class Gyro
{
    public:

    Gyro();

    ~Gyro();

    double requestData();

    long filter(int count, int eixoValue);

    private:

    Gyro *gyroscope;

};


#endif