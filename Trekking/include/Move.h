#ifndef MOVE_H
#define MOVE_H

#include <MotorDC.h>
#include <Gyro.h>
#include <VisionSensor.h>

#define HORARIO 0
#define ANTIHORARIO 1
#define DIAMETER 12 // roda tem 12,22cm de diametro
#define PI 3.14159265359
#define GIRO 400 // o enconder conta 400 para dar 1 giro na roda
// #define WDIST 5 //distancia entre as duas rodas em cm
#define WDIST 12 // distancia entre as duas rodas em cm

/* Move All
  Descricao: Liga os dois motor6es.
  Parâmetros:
    - potencia: Potência desejada.
*/

void moveAll(int potencia, MotorDC *motorLeft, MotorDC *motorRight);
// Por causa do encoder no objeto MotorDC a gente usa o ponteiro.

/* Stop All
  Descricao: Desliga os dois motores.
*/

void moveAllpid(int _potencia, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, float giro, long *powerRightL);

void moveRevAll(int potencia, MotorDC *motorLeft, MotorDC *motorRight);

void stopAll(MotorDC *motorLeft, MotorDC *motorRight);

void stop2(MotorDC *motorLeft, MotorDC *motorRight);

/* Turn Clockwise
  Descricao: Gira no sentido horário.
  Parâmetros:
    - potencia: Potência desejada.
*/

void turnClockwise(int _power, MotorDC *motorLeft, MotorDC *motorRight);

/* Turn Anti Clockwise
  Descricao: Gira no sentido anti horário.
  Parâmetros:
    - potencia: Potência desejada.
*/

void turnAnticlockwise(int _power, MotorDC *motorLeft, MotorDC *motorRight);

/* Calculate Final Angle
  Descricao: Baseado no nosso círculo trigonométrico, calcula o ângulo final no magnetômtero.
  Parâmetros:
    - _desiredDegrees: Quantos ângulos a virar.
    - _currentDegrees: Ângulo atual.
*/

long calculateFinalAngle(long _desiredDegrees, long _currentDegrees);

/* Turn Degrees
  Descricao: Gira em uma determinada direção, determinada quantidade de graus utilizando os encoders.
  Parâmetros:
    - _power: Potência desejada.
    - _degrees: Quantidade de graus que se deseja girar.
    - _clock: Direção desejada HORARIO OU ANTIHORARIO
*/

void turnDegrees(int _power, int _degrees, int _clock, MotorDC *motorLeft, MotorDC *motorRight);


/* turnDegreesGyro2
  Descricao: Função que o David e Arthur tava fazendo Gira em uma determinada direção, determinada quantidade de graus utilizando o giroscopio.
  Parâmetros:
    - _power: Potência desejada.
    - _degrees: Quantidade de graus que se deseja girar.
    - _clock: Direção desejada HORARIO OU ANTIHORARIO
*/

void turnDegreesGyro2(int _power, long _degrees, int _clock, MotorDC *motorLeft, MotorDC *motorRight, Gyro *giroscopio);

/* turnToDesiredAngleGyro
  Descricao: Função que o David fez, gira em uma determinada direção, para um grau específico,
  utilizando o giroscopio. A direção do giro será feita com base na menor distância entre o
  ângulo atual e o ângulo desejado.
  Parâmetros:
    - _power: Potência desejada.
    - _desiredDegree: Grau que se deseja que o robô esteja de frente para.
*/

void turnToDesiredAngleGyro(int _power, long _desiredDegree, MotorDC *motorLeft, MotorDC *motorRight, Gyro *giroscopio);

/* Foward Cm
  Descricao: Anda para frente uma certa quantidade de centímetros.
  Parâmetros:
    - potencia: Potência desejada.
    - distancia: Distância em centímetros.
*/

void ForwardCm(int _power, long _distance, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, Gyro *giroscopio, long *powerRightL, int valueRef);

/* Rev Cm
  Descricao: Anda para trás uma certa quantidade de centímetros.
  Parâmetros:
    - potencia: Potência desejada.
    - distancia: Distância em centímetros.
*/

void RevCm(int _power, int _distance, MotorDC *motorLeft, MotorDC *motorRight);

void moveAllpidGyro(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, Gyro *giroscopio, long *powerRightL, long valueRef);

void moveAllpidGyroNew(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, Gyro *giroscopio, long *powerRightL, long valueRef);

void moveAllpidVision(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, Gyro *giroscopio, long *powerRightL, long valueRef, VisionSensor& _camera);


#endif