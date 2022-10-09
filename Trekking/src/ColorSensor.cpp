// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCAO NOVA QUE FIZEMOS!!!!!!!!!!!!!!
// https://www.usinainfo.com.br/blog/projeto-arduino-sensor-de-cor-verificando-cores-com-tcs230-e-led-rgb/
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <Arduino.h>
#include <ColorSensor.h>
#include <string.h>

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

    // Analisa se a menor frequencia é vermelha
    if (this->red < this->green && this->red < this->blue)
    {
        // Analisa AMARELO
        if ((this->green - this->red) < 90) // da pra aumentar esse valor, quando tá só vermelho a diferença fica por volta de 100 ou mais
        {
            // Serial.println("AMARELOOO!!!!");
            // Serial.print("R: ");
            // Serial.print(this->red);
            // Serial.print(" G: ");
            // Serial.print(this->green);
            // Serial.print(" B: ");
            // Serial.println(this->blue);
            // Serial.println(this->green - this->red);
            strcpy(this->currentColor, "yellow");
        }
        else
        {
            // Serial.print("vermelhoooo!!!! ");
            // Serial.print("R: ");
            // Serial.print(this->red);
            // Serial.print(" G: ");
            // Serial.print(this->green);
            // Serial.print(" B: ");
            // Serial.println(this->blue);
            // Serial.println(this->green - this->red);
            strcpy(this->currentColor, "red");
        }
    }

    // Analisa se a menor frequencia é verde
    else if (this->green < this->red && this->green < this->blue)
    {
        // Serial.print("verdeeeeeeeee!!!! ");
        // Serial.print("R: ");
        // Serial.print(this->red);
        // Serial.print(" G: ");
        // Serial.print(this->green);
        // Serial.print(" B: ");
        // Serial.println(this->blue);
        strcpy(this->currentColor, "green");
    }

    // Analisa se a menor frequencia é azul
    else if (this->blue < this->red && this->blue < this->green)
    {
        // Serial.print("azuuuuuuuul!!!! ");
        // Serial.print("R: ");
        // Serial.print(this->red);
        // Serial.print(" G: ");
        // Serial.print(this->green);
        // Serial.print(" B: ");
        // Serial.println(this->blue);
        strcpy(this->currentColor, "blue");
    }
}