#include <Arduino.h>
#include <MotorDC.h>
#include <ColorSensor.h>
#include <Ultrasonic.h>
#include <UltrasonicFilter.h>
#include <Move.h>
#include <Gyro.h>
#include <Wire.h>
#include <defines.h>
#include <VisionSensor.h>


MotorDC motorRight(pin2A, pin2B, pin2pwm, pin2Enc, pinEnable2);
MotorDC motorLeft(pin1A, pin1B, pin1pwm, pin1Enc, pinEnable1);
Gyro *giroscopio = new Gyro();
VisionSensor camera(VISION_START);
Ultrasonic ultrasonic2(US2Trigger, US2Echo);
Ultrasonic ultrasonic3(US3Trigger, US3Echo);
Ultrasonic ultrasonic4(US4Trigger, US4Echo);
ColorSensor corSen(ColorSensorS0, ColorSensorS1, ColorSensorS2, ColorSensorS3, ColorSensorOut);

int machineState = 0;                               // Máquina de Estados
float valueRef;                                     // Magnetômetro
float *filtered_values;                             // Ultrassons
float soma = 0, error[2];                           // Controle
long powerRightL = 100;                             // Controle
int potencia = 100;                                 // Potencia Base do robô   
int potenciaGiro = 130;                             // Potência para girar
int cameraResult = 180;                             // Visão
long firstTime;                                     // Primeiro instante de tempo

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

//Módulo Giroscópio/Acelerômetro/Magnetômetro - comunicação i2c
    Wire.begin();
    // Inicializa o HMC5883
    Wire.beginTransmission(address); //Endereço base + offset para o magnetômetro
    // Seleciona o modo
    Wire.write(0x02);
    // Modo de medicao continuo
    Wire.write(0x00);
    Wire.endTransmission();

// Interrupão dos Encoders
    uint8_t pin1Interrupt = digitalPinToInterrupt(pin1Enc);
    uint8_t pin2Interrupt = digitalPinToInterrupt(pin2Enc);
    attachInterrupt(pin1Interrupt, incR, RISING);
    attachInterrupt(pin2Interrupt, incL, RISING);

    error[0] = 0;
    error[1] = millis();

    pinMode(SinalLuminoso, OUTPUT);
    digitalWrite(SinalLuminoso, LOW);

    delay(2000);
}

//Primeiro Marco
void firstPart(){
    long now = millis();

    while (true){
        if (machineState == 0)
        {
            //Pega a primeira leitura do Giroscópio como referência de "frente"
            for (size_t i = 0; i < 20; i++)
            {
            valueRef += giroscopio->requestData();
            }
            valueRef = valueRef/20;

            //Move pela bússola antes de ativar a visão
            moveAllpidGyroNew(potencia + 20, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
            
            Serial.print("valueRef: ");
            Serial.println(valueRef);
            firstTime = millis();
            machineState = 1;
        }

        // Após 4 segundos, inicia controle por visão
        if(millis() - firstTime > 4000)
        {
            cameraResult = camera.getFilteredAngle();
        }

        if(cameraResult < 170)
        {
            
            moveAllpidVision(potencia, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, 90, camera);
            //digitalWrite(SinalLuminoso, HIGH);
            Serial.print("Camera: ");
            Serial.println(cameraResult);
        }
        else
        {
            motorLeft.fwd(potencia-20);
            motorRight.fwd(potencia-60);
            //digitalWrite(SinalLuminoso, LOW);
        }

        filtered_values = simpleProximity(ultrasonic2, ultrasonic3, ultrasonic4);

        //corSen.readColor();

        if(filtered_values[1] < 45 || filtered_values[0] < 45 ||filtered_values[2] < 45 ){//|| strcmp(corSen.currentColor, "yellow") == 0) {
            digitalWrite(SinalLuminoso, HIGH);
            stopAll(&motorLeft, &motorRight);
            delay(1000);
            digitalWrite(SinalLuminoso, LOW);
            moveRevAll(potencia, &motorLeft, &motorRight);
            delay(500);
            stopAll(&motorLeft, &motorRight);
            turnToDesiredAngleGyro(potenciaGiro, -105, &motorLeft, &motorRight, giroscopio);
            machineState = 2;
            delay(100);
            Serial.println("FIRST DONE");
            return;
        } else {
            digitalWrite(SinalLuminoso, LOW);
            //moveAllpidGyroNew(100, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
        }
    }
}

void secondPart()
{
    if(machineState == 2)
    {
        for (size_t i = 0; i < 20; i++)
        {
            valueRef += giroscopio->requestData();
        }
        valueRef = valueRef/20;
        moveAllpidGyroNew(potencia+20, &motorLeft, &motorRight, &soma, error, giroscopio, &powerRightL, valueRef);
        machineState = 3;
    }

    if(machineState == 3)
    {
        if(filtered_values[1] < 70 || filtered_values[0] < 70 ||filtered_values[2] < 70 ) {
        stopAll(&motorLeft, &motorRight);
        delay(400);
        moveRevAll(potencia, &motorLeft, &motorRight);
        delay(1000);
        stopAll(&motorLeft, &motorRight);
        turnDegreesGyro2(potenciaGiro, 90, HORARIO, &motorLeft, &motorRight, giroscopio);
        delay(200);
        }

    }
}

void loop()
{
    firstPart();
    secondPart();


    // stopAll(&motorLeft, &motorRight);
}
