#ifndef SENSORCOLOR_H
#define SENSORCOLOR_H

class SensorColor {
private:
    int pinColorS0;
    int pinColorS1;
    int pinColorS2;
    int pinColorS3;
    int pinColorOut;
public:
    int vermelho = 0;
    int verde = 0;
    int azul = 0;

    SensorColor(int pinColorS0, int pinColorS1, int pinColorS2, int pinColorS3, int pinColorOut);
    void readColors();
};

#endif