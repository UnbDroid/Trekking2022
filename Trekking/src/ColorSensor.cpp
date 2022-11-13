// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCAO NOVA QUE FIZEMOS!!!!!!!!!!!!!!
// https://www.usinainfo.com.br/blog/projeto-arduino-sensor-de-cor-verificando-cores-com-tcs230-e-led-rgb/
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <Arduino.h>
#include <ColorSensor.h>
#include <string.h>

#define R 0
#define G 1
#define B 2

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

    char string[1024];
    sprintf(string, "RGB [%d] [%d] [%d]", this->red, this->green, this->blue);



    Serial.println(string);

    int limiarRGB_Yellow[3] = {150, 150, 200};
    int limiarRGB_Green[3] = {112, 78, 86};
    int limiarRGB_Red[3] = {33, 84, 66};
    int errorAmplitude = 10;

    //TODO implement binary space partitioning
    // save in file

    if(this->red <= limiarRGB_Yellow[R]+errorAmplitude && this->red <= limiarRGB_Yellow[G]+errorAmplitude && this->red <= limiarRGB_Yellow[B]+errorAmplitude ) {
        strcpy(this->currentColor, "yellow");
    } else {
        strcpy(this->currentColor, "green");
    };
}