// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCAO NOVA QUE FIZEMOS!!!!!!!!!!!!!!
// https://www.usinainfo.com.br/blog/projeto-arduino-sensor-de-cor-verificando-cores-com-tcs230-e-led-rgb/
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <Arduino.h>
#include <ColorSensor.h>
#include <string.h>

#include <EEPROM.h>

#define R 0
#define G 1
#define B 2

#define addressYellowR 0
#define addressYellowG 1
#define addressYellowB 2

#define addressGreenR 3
#define addressGreenG 4
#define addressGreenB 5

#define addressRedR 6
#define addressRedG 7
#define addressRedB 8

void ColorSensor::fetchCalibrationFromEPPROM()
{
    this->limiarRGB_Yellow[R] = EEPROM.read(addressYellowR);
    this->limiarRGB_Yellow[G] = EEPROM.read(addressYellowG);
    this->limiarRGB_Yellow[B] = EEPROM.read(addressYellowB);

    this->limiarRGB_Green[R] = EEPROM.read(addressGreenR);
    this->limiarRGB_Green[G] = EEPROM.read(addressGreenG);
    this->limiarRGB_Green[B] = EEPROM.read(addressGreenB);

    this->limiarRGB_Red[R] = EEPROM.read(addressRedR);
    this->limiarRGB_Red[G] = EEPROM.read(addressRedG);
    this->limiarRGB_Red[B] = EEPROM.read(addressRedB);
}

void ColorSensor::writeCalibrationOnEPPROM()
{
    EEPROM.write(addressYellowR, this->limiarRGB_Yellow[R]);
    EEPROM.write(addressYellowG, this->limiarRGB_Yellow[G]);
    EEPROM.write(addressYellowB, this->limiarRGB_Yellow[B]);

    EEPROM.write(addressGreenR, this->limiarRGB_Green[R]);
    EEPROM.write(addressGreenG, this->limiarRGB_Green[G]);
    EEPROM.write(addressGreenB, this->limiarRGB_Green[B]);

    EEPROM.write(addressRedR, this->limiarRGB_Red[R]);
    EEPROM.write(addressRedG, this->limiarRGB_Red[G]);
    EEPROM.write(addressRedB, this->limiarRGB_Red[B]);
}

ColorSensor::ColorSensor(int ColorSensorS0, int ColorSensorS1, int ColorSensorS2, int ColorSensorS3, int ColorSensorOut)
{
    this->ColorSensorS0 = ColorSensorS0;
    this->ColorSensorS1 = ColorSensorS1;
    this->ColorSensorS2 = ColorSensorS2;
    this->ColorSensorS3 = ColorSensorS3;
    this->ColorSensorOut = ColorSensorOut;

    pinMode(ColorSensorS0, OUTPUT); // Pino S0 configurado como saida
    pinMode(ColorSensorS1, OUTPUT); // Pino S1 configurado como saida
    pinMode(ColorSensorS2, OUTPUT); // Pino S2 configurado como saida
    pinMode(ColorSensorS3, OUTPUT); // Pino S3 configurado como saida
    pinMode(ColorSensorOut, INPUT); // Pino OUT configurado como entrada

    // Configura a escala de frequência para 20%
    digitalWrite(ColorSensorS0, HIGH);
    digitalWrite(ColorSensorS1, LOW);

    this->fetchCalibrationFromEPPROM();
}

void ColorSensor::readColor()
{
    // Configura a leitura para os fotodiodos Red (Vermelho)
    digitalWrite(ColorSensorS2, LOW);
    digitalWrite(ColorSensorS3, LOW);
    delay(50);

    // Lê a frequencia de saída do fotodiodo vermelho
    this->red = pulseIn(ColorSensorOut, LOW);

    // Configura a leitura para os fotodiodos Green (Verde)
    digitalWrite(ColorSensorS2, HIGH);
    digitalWrite(ColorSensorS3, HIGH);
    delay(50);

    // Lê a frequencia de saída do fotodiodo verde
    this->green = pulseIn(ColorSensorOut, LOW);

    // Configura a leitura para os fotodiodos Blue (Azul)
    digitalWrite(ColorSensorS2, LOW);
    digitalWrite(ColorSensorS3, HIGH);
    delay(50);

    // Lê a frequencia de saída do fotodiodo azul
    this->blue = pulseIn(ColorSensorOut, LOW);

    // char string[1024];
    // sprintf(string, "RGB [%d] [%d] [%d]", this->red, this->green, this->blue);

    // save in file
    this->readCalibration();
    this->findNearest();
}

void ColorSensor::calibrate()
{
    // TODO
}

void ColorSensor::readCalibration()
{
    Serial.print("Yellow Calibration");
    char string2[1024];
    sprintf(string2, "RGB [%d] [%d] [%d]",
            this->limiarRGB_Yellow[0],
            this->limiarRGB_Yellow[1],
            this->limiarRGB_Yellow[2]);
    Serial.println(string2);

    Serial.print("Green Calibration");
    sprintf(string2, "RGB [%d] [%d] [%d]",
            this->limiarRGB_Green[0],
            this->limiarRGB_Green[1],
            this->limiarRGB_Green[2]);
    Serial.println(string2);

    Serial.print("Red Calibration");
    sprintf(string2, "RGB [%d] [%d] [%d]",
            this->limiarRGB_Red[0],
            this->limiarRGB_Red[1],
            this->limiarRGB_Red[2]);
    Serial.println(string2);
}

void ColorSensor::findNearest()
{
    int errorAmplitude = 10;
    if (this->red <= limiarRGB_Yellow[R] + errorAmplitude && this->red >= limiarRGB_Yellow[R] - errorAmplitude)
    {
        strcpy(this->currentColor, "yellow");
    }
    else if (this->red <= limiarRGB_Green[R] + errorAmplitude && this->red >= limiarRGB_Green[R] - errorAmplitude)
    {
        strcpy(this->currentColor, "green");
    }
    else if (this->red <= limiarRGB_Red[R] + errorAmplitude && this->red >= limiarRGB_Red[R] - errorAmplitude)
    {
        strcpy(this->currentColor, "red");
    }
    else
    {
        strcpy(this->currentColor, "red");
    }
}