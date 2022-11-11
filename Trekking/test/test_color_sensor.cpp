#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>

int firstReading = true;

ColorSensor *colorSensor = new ColorSensor(ColorSensorS0, ColorSensorS1, ColorSensorS2, ColorSensorS3, ColorSensorOut);

unsigned long tPrint;

void setup()
{
    Serial.begin(9600);
    Wire.begin();

    // Inicializa o HMC5883
    Wire.beginTransmission(address);
    // Seleciona o modo
    Wire.write(0x02);
    // Modo de medicao continuo
    Wire.write(0x00);
    Wire.endTransmission();

}

void loop()
{
    // Delay para começar
    if (firstReading)
    {
        firstReading = false;
        delay(6000);
    }
    colorSensor->readColor();
    Serial.print("Cor lida: ");
    Serial.println(colorSensor->currentColor);
    delay(1000);
}
