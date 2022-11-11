#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>
#include <VisionSensor.h>

int firstReading = true;
int count = 0;
int valueRef;

MotorDC motorRight(pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);
MotorDC motorLeft(pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1);

VisionSensor camera(VISION_START);

Gyro *giroscopio = new Gyro();

float soma = 0;
float error[2];
long powerRightL = 70;
unsigned long tPrint;
int x, y, z;

int potencia = 120;
int distanciaCm = 200;
int rightEncoderReading = motorRight.getCount();
int leftEncoderReading = motorLeft.getCount();
int cameraAngle = 90;

void incL()
{
    motorLeft.encSignal();
}

void incR()
{
    motorRight.encSignal();
}

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

    uint8_t pin1Interrupt = digitalPinToInterrupt(pin1Enc);
    uint8_t pin2Interrupt = digitalPinToInterrupt(pin2Enc);

    attachInterrupt(pin1Interrupt, incR, RISING); // VERIFICAR
    attachInterrupt(pin2Interrupt, incL, RISING);
    error[0] = 0;
    error[1] = millis();

    delay(2000);
    tPrint = millis();
}

void loop() 
{
    // Delay para começar
    if (firstReading)
    {
        firstReading = false;
        delay(1000);
    }

    //moveAll(potencia, &motorLeft, &motorRight);
    motorLeft.fwd(potencia+20);
    motorRight.rev(potencia+20);
    delay(32000);
    motorLeft.fwd(potencia);
    motorRight.fwd(potencia);
    Serial.println("Move\n");
    delay(2000);
    Serial.println("Move stop\n");
    motorLeft.fwd(potencia);
    motorRight.fwd(potencia-100);
    delay(80000);

    stopAll(&motorLeft, &motorRight);
    
    while(true)
    {
        cameraAngle = camera.getFilteredAngle();
        Serial.println(cameraAngle);
        if(cameraAngle > 100)
        {
            motorLeft.fwd(potencia);
            motorRight.fwd(potencia-20);
        }
        else if(cameraAngle < 80)
        {
            motorLeft.fwd(potencia-20);
            motorRight.fwd(potencia);
        }
        else
        {
            motorLeft.fwd(potencia);
            motorRight.fwd(potencia);
        }
    }

    Serial.println("\n\nStopped moving\n\n");

    rightEncoderReading = motorRight.getCount();
    leftEncoderReading = motorLeft.getCount();

    Serial.print("Right Encoder: ");
    Serial.println(rightEncoderReading);
    Serial.print("Left Encoder: ");
    Serial.println(leftEncoderReading);
    delay(1000);
}
