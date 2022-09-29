// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
// FUNCAO NOVA QUE FIZEMOS!!!!!!!!!!!!!!
// https://www.usinainfo.com.br/blog/projeto-arduino-sensor-de-cor-verificando-cores-com-tcs230-e-led-rgb/
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#include <Arduino.h>
#include <ColorSensor.h>
#include <string.h>

ColorSensor::ColorSensor(int pinColorS0, int pinColorS1, int pinColorS2, int pinColorS3, int pinColorOut)
{
    this->pinColorS0 = pinColorS0;
    this->pinColorS1 = pinColorS1;
    this->pinColorS2 = pinColorS2;
    this->pinColorS3 = pinColorS3;
    this->pinColorOut = pinColorOut;

    pinMode(pinColorS0, OUTPUT); // Pino S0 configurado como saida
    pinMode(pinColorS1, OUTPUT); // Pino S1 configurado como saida
    pinMode(pinColorS2, OUTPUT); // Pino S2 configurado como saida
    pinMode(pinColorS3, OUTPUT); // Pino S3 configurado como saida
    pinMode(pinColorOut, INPUT); // Pino OUT configurado como entrada

    // Configura a escala de frequência para 20%
    digitalWrite(pinColorS0,HIGH);
    digitalWrite(pinColorS1,LOW);
}

void ColorSensor::readColor()
{
    // Configura a leitura para os fotodiodos Red (Vermelho)
    digitalWrite(pinColorS2,LOW);
    digitalWrite(pinColorS3,LOW);
    delay(50);

    // Lê a frequencia de saída do fotodiodo vermelho
    this->red = pulseIn(pinColorOut, LOW);

    // Configura a leitura para os fotodiodos Green (Verde)
    digitalWrite(pinColorS2,HIGH);
    digitalWrite(pinColorS3,HIGH);
    delay(50);

    // Lê a frequencia de saída do fotodiodo verde
    this->green = pulseIn(pinColorOut, LOW);

    // Configura a leitura para os fotodiodos Blue (Azul)
    digitalWrite(pinColorS2,LOW);
    digitalWrite(pinColorS3,HIGH);
    delay(50);

    // Lê a frequencia de saída do fotodiodo azul
    this->blue = pulseIn(pinColorOut, LOW);

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
    else if (this->green < this->red && this->green < this->blue) {
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
    else if (this->blue < this->red && this->blue < this->green) {
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