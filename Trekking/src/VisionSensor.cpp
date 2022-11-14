#include <Arduino.h>
#include <VisionSensor.h>

VisionSensor::VisionSensor(int _pinStart)
{
    this->m_pinStart = _pinStart;

    pinMode(37, INPUT);
    for(int i = m_pinStart; i < m_pinStart + (8*2); i+=2)
    {
        pinMode(i, INPUT);
    }
}

int VisionSensor::getAngle()
{
    uint8_t newReading = 0;
    int currentPin = 0;

    newReading |= digitalRead(37) << 7;
    Serial.print(digitalRead(37));
    for(int i = m_pinStart; i < m_pinStart + (8*2); i+=2)
    {
        int thpin = digitalRead(i);
        newReading |= thpin << (6 - currentPin);
        currentPin += 1;
        Serial.print(thpin);
    }
    Serial.println();

    return newReading;
}

int VisionSensor::getFilteredAngle()
{
    uint8_t newReading = getAngle();

    if(abs(newReading-m_lastReading) > 15)
    {
        newReading = m_lastReading+(newReading-m_lastReading)/8;
    }
    m_lastReading = newReading;

    return newReading;
}