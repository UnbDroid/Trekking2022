#ifndef MAG_H
#define MAG_H
#include <Arduino.h>
#include <Wire.h>
#define address 0x3C 


class Magnet
{
    public:

    Magnet();

    ~Magnet();

    double requestData();

    long filter(int count, int eixoValue);

    private:
    int m_scl, m_sda;

    Magnet *magnetometer;

};


#endif