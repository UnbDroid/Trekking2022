#include <Arduino.h>
#include <Ultrasonic.h>
#include <defines.h>

Ultrasonic ultrasonic(pinUS1Trigger, pinUS1Echo);

void setup() {
    Serial.begin(9600);
}

void loop() {
    //Le as informacoes do sensor, em cm e pol
    float cmMsec, inMsec;
    long microsec = ultrasonic.timing();
    cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
    inMsec = ultrasonic.convert(microsec, Ultrasonic::IN);
    //Exibe informacoes no serial monitor
    Serial.print("Distancia em cm: ");
    Serial.print(cmMsec);
    Serial.print(" - Distancia em polegadas: ");
    Serial.println(inMsec);
    delay(1000);
}

