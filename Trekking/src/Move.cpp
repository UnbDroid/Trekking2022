#include <Arduino.h>
#include <Move.h>
#include <math.h>

#define kp 0.2
#define ki 0.75

/*Encoder

#define kp 0.2
#define ki 0.001

*/
float time1 = millis();

// Função que move as duas rodas para a frente.
void moveAll(int _power, MotorDC *motorLeft, MotorDC *motorRight)
{
  motorLeft->fwd(_power);
  motorRight->fwd(_power);
}

// Função que move as duas para frente, porém usando o PID.
void moveAllpid(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, float giro, long *powerRightL)
{
  float powerLeft;
  float powerRight;

  float lastT = error[1];
  float deltaT;

  float mLeft = motorLeft->getCount();
  float mRight = motorRight->getCount();
  error[0] = (mLeft - mRight); // - giro; // diferença entre os encoderes sendo o error atual
  error[1] = millis();
  Serial.println(error[0]);

  deltaT = (error[1] - lastT) / 1000;

  *soma = (*soma) * 0.6 + error[0] * deltaT;

  if ((*soma) * ki > 10)
  {
    *soma = 10 / ki;
  }
  else if ((*soma) * ki < -10)
  {
    *soma = -10 / ki;
  }

  powerLeft = abs(_power);
  powerRight = abs((*powerRightL)) + (error[0] * kp) + (*soma) * ki;
  Serial.println("LEFT");
  Serial.println(powerLeft);
  Serial.println("right");
  Serial.println(powerRight);

  powerLeft = (powerLeft > 255) ? 255 : powerLeft;
  powerRight = (powerRight > 255) ? 255 : powerRight;
  powerLeft = (powerLeft < 0) ? 0 : powerLeft;
  powerRight = (powerRight < 0) ? 0 : powerRight;

  motorLeft->fwd(powerLeft);
  motorRight->fwd(powerRight);
  *powerRightL = powerRight;

  // Quando a potência era negativa, adotamos que o robô andaria para trás
  if (_power < 0)
  {

    if ((error[1] - time1) > 3500)
    {
      motorLeft->rev(powerLeft);
      motorRight->rev(powerRight);
    }
    else
    {
      motorLeft->rev(50);
      motorRight->rev(50);
    }
  }
  else
  {
    if ((error[1] - time1) > 3500)
    {
      motorLeft->fwd(powerLeft);
      motorRight->fwd(powerRight);
    }
    else
    {
      motorLeft->fwd(50);
      motorRight->fwd(50);
    }
  }
}

// Função que move as duas rodas para trás.
void moveRevAll(int _power, MotorDC *motorLeft, MotorDC *motorRight)
{
  motorLeft->rev(_power);
  motorRight->rev(_power);
}

// Função que para as duas rodas.
void stopAll(
    MotorDC *motorLeft,
    MotorDC *motorRight)
{
  motorRight->stop();
  motorLeft->stop();
}

void stop2(
    MotorDC *motorLeft,
    MotorDC *motorRight)
{
  for (int i = 60; i > 0 ; i--)
  {
    Serial.print(i);
    motorRight->fwd(i);
    motorLeft->fwd(i);
    delay(2);
  }
  stopAll(motorLeft,motorRight);
}

// Andar para frente uma certa distância.
void ForwardCm(
    int _power,
    long _distance,
    MotorDC *motorLeft,
    MotorDC *motorRight,
    float *soma,
    float *error,
    Gyro *giroscopio,
    long *powerRightL,
    int valueRef)
{
  // ------------------------------------------------------------------------------------------------
  // A funcao moveAllpidGyro nao funciona quando chama aqui dentro, ai pra testar a gente
  // mudou na moveAll para o direito andar com _power-30
  // E nao mudamos o valor de GIRO, ai por isso ta andando um pouco mais do que o valor especificado,
  // tem que ver um jeito melhor de medir o GIRO
  // ------------------------------------------------------------------------------------------------

  int countLeftInitial = motorLeft->getCount();
  int countLeftUpdate = motorLeft->getCount();
  long c = DIAMETER * PI;
  long move = (_distance * GIRO) / c;

  // moveAll(_power, motorLeft, motorRight);
  moveAllpidGyro(_power, motorLeft, motorRight, soma, error, giroscopio, powerRightL, valueRef);

  // Enquanto distância entre o enconder atual e o inicial não for o desejado (MOVE) ele vai continuar andando pra frente.
  while ((countLeftUpdate - countLeftInitial) < move)
  {
    // moveAll(_power, motorLeft, motorRight);
    moveAllpidGyro(_power, motorLeft, motorRight, soma, error, giroscopio, powerRightL, valueRef);
    countLeftUpdate = motorLeft->getCount();
    // Serial.print("countLeftUpdate: ");
    // Serial.println(countLeftUpdate);
    // Serial.print("countLeftInitial: ");
    // Serial.println(countLeftInitial);
    // Serial.print("move: ");
    // Serial.println(move);
  }
  stopAll(motorLeft, motorRight);
}

// TODO All bellow

// Função que gira o robô no sentido horário.
void turnClockwise(int _power, MotorDC *motorLeft, MotorDC *motorRight)
{
  // stopAll(motorLeft, motorRight);
  motorLeft->fwd(_power);
  motorRight->rev(_power);
  // delay(120);
  // stopAll(motorLeft, motorRight);
}

// Função que gira o robô no sentido antihorário.
void turnAnticlockwise(int _power, MotorDC *motorLeft, MotorDC *motorRight)
{
  stopAll(motorLeft, motorRight);
  motorRight->fwd(_power);
  motorLeft->rev(_power);
  delay(120);
  stopAll(motorLeft, motorRight);
}

// Função que gira o robô de acordo com o graus usando encoders.
// dir = HORARIO ou ANTIHORARIO
void turnDegrees(int _power, int _degree, int _clock, MotorDC *motorLeft, MotorDC *motorRight)
{
  int c = DIAMETER * 3.14;
  // Perimetro que a roda deve andar para chegar na quantidade de graus desejada
  int move = (GIRO * (WDIST * 3.14 * 2) * ((float)_degree / 360)) / c;

  // Variáveis que armazenam as contagens dos encoderes
  int countLeftInitial = motorLeft->getCount();
  int countLeftUpdate = motorLeft->getCount();
  int countRightInitial = motorRight->getCount();
  int countRightUpdate = motorRight->getCount();

  // Girar sentido horário
  if (_clock == HORARIO)
  {
    motorLeft->fwd(_power);
    motorRight->rev(_power);
    // Enquanto distância entre o enconder atual e o inicial não for o desejado (MOVE) ele vai continuar girando.
    while ((countLeftUpdate - countLeftInitial) < move)
    {
      countLeftUpdate = motorLeft->getCount();
      Serial.println("Counter L deg");
      Serial.println(countLeftUpdate);
    }
    // Quando a distância do enconder atual e o inicial for igual o desejado (MOVE), o robô tem que parar de girar.
    stopAll(motorLeft, motorRight);
  }

  else if (_clock == ANTIHORARIO)
  {
    motorRight->fwd(_power);
    motorLeft->rev(_power);
    while ((countRightUpdate - countRightInitial) < move)
    {
      countRightUpdate = motorRight->getCount();
      Serial.println("Counter R");
      Serial.println(countRightUpdate);
    }
    stopAll(motorLeft, motorRight);
  }
  else
  {
    // error
  }
  stopAll(motorLeft, motorRight);
}

// David e Arthur Função que gira o robô de acordo com o graus usando giroscopio.
// dir = HORARIO ou ANTIHORARIO
void turnDegreesGyro2(int _power, long _degree, int _clock, MotorDC *motorLeft, MotorDC *motorRight, Gyro *giroscopio)
{
  bool flag = false;
  long ang_inicial = giroscopio->requestData();
  long ang_atual;

  // Serial.print("ang_inicial: ");
  // Serial.println(ang_inicial);

  if (_clock == HORARIO)
  {
    motorLeft->fwd(_power);
    motorRight->rev(_power);

    long ang_final = ang_inicial - _degree;

    // Serial.print("ang_final antes: ");
    // Serial.println(ang_final);

    // Se estiver com um ângulo negativo e for para um ângulo final positivo(passa pelo +- 180º)
    if (ang_inicial < 0 && ang_final < -180)
    {
      ang_final += 360; // transforma o angulo final em positivo
      flag = true;
    }

    // Serial.print("ang_final depois: ");
    // Serial.println(ang_final);

    while (true)
    {
      ang_atual = giroscopio->requestData();
      Serial.print("ang_atual: ");
      Serial.println(ang_atual);
      // Se estiver com um ângulo negativo e for para um ângulo final positivo(passa pelo +- 180º)
      if (flag && ang_atual > 0 && ang_atual <= ang_final)
      {
        break;
      }
      if (!flag && ang_atual <= ang_final)
      {
        break;
      }
    }
    stopAll(motorLeft, motorRight);
  }
  else if (_clock == ANTIHORARIO)
  {
    motorLeft->rev(_power);
    motorRight->fwd(_power);

    long ang_final = ang_inicial + _degree;

    // Serial.print("ang_final antes: ");
    // Serial.println(ang_final);

    // Se estiver com um ângulo positivo e for para um ângulo final negativo(passa pelo +- 180º)
    if (ang_inicial > 0 && ang_final > 180)
    {
      ang_final -= 360; // transforma o angulo final em negativo
      flag = true;
    }
    // Serial.print("ang_final depois: ");
    // Serial.println(ang_final);
    while (true)
    {
      ang_atual = giroscopio->requestData();
      // Serial.print("ang_atual: ");
      // Serial.println(ang_atual);
      // Se estiver com um ângulo positivo e for para um ângulo final negativo(passa pelo +- 180º)
      if (flag && ang_atual < 0 && ang_atual >= ang_final)
      {
        break;
      }
      if (!flag && ang_atual >= ang_final)
      {
        break;
      }
    }
    stopAll(motorLeft, motorRight);
  }

  // Serial.print("ang_final: ");
  // Serial.println(ang_atual);
}

// Andar para trás uma certa distância
void RevCm(int _power, int _distance, MotorDC *motorLeft, MotorDC *motorRight)
{
  int countLeft = 0;
  int c = DIAMETER * PI;
  int move = (_distance * GIRO) / c;

  moveRevAll(_power, motorLeft, motorRight);

  while (countLeft < move)
  {
    countLeft = motorLeft->getCount();
  }

  stopAll(motorLeft, motorRight);
}

void moveAllpidGyro(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, Gyro *giroscopio, long *powerRightL, long valueRef)
{
  float powerLeft;
  float powerRight;

  float lastT = error[1];
  float lastE = error[0];
  float deltaT;

  long gyroValue = giroscopio->requestData();

  error[0] = (gyroValue - valueRef); // diferença entre os encoderes sendo o error atual
  error[1] = millis();

  // Caso esteja proximo de 0
  if (error[0] > -3 && error[0] < 3)
  {
    error[0] = 0;
  }

  // Caso esteja no angulo que passa de +180 para -180
  if (error[0] <= -180)
  {
    error[0] += 360;
  }
  if (error[0] >= 180)
  {
    error[0] -= 360;
  }

  // TESTE
  // Serial.print(" gyroValue : ");
  // Serial.print(gyroValue);
  // Serial.print(" valueRef : ");
  // Serial.print(valueRef);
  // Serial.print(" error[0] : ");
  // Serial.println(error[0]);

  deltaT = (error[1] - lastT) / 1000;

  *soma = (*soma) * 0.6 + error[0] * deltaT;

  if ((*soma) * ki > 10)
  {
    *soma = 10 / ki;
  }
  else if ((*soma) * ki < -10)
  {
    *soma = -10 / ki;
  }

  powerLeft = abs((*powerRightL)) + (error[0] * kp + (*soma));
  powerRight = abs(_power); //+ (*soma)*ki;
  // Serial.print(" powerRight : ");
  // Serial.println(powerRight);

  powerLeft = (powerLeft > 255) ? 255 : powerLeft;
  powerRight = (powerRight > 255) ? 255 : powerRight;
  powerLeft = (powerLeft < 0) ? 0 : powerLeft;
  powerRight = (powerRight < 0) ? 0 : powerRight;

  // TESTE
  Serial.print(" powerLeft : ");
  Serial.print(powerLeft);
  Serial.print(" powerRight : ");
  Serial.println(powerRight);

  motorLeft->fwd(powerLeft);
  motorRight->fwd(powerRight);
  *powerRightL = (powerRight < powerLeft * 0.4) ? *powerRightL : powerRight;
  // *powerRightL = powerRight;

  // Quando a potência era negativa, adotamos que o robô andaria para trás
  //  if(_power < 0){

  //   if((error[1] - time1) > 3500){
  //     motorLeft->rev(powerLeft);
  //     motorRight->rev(powerRight);
  //   } else {
  //     motorLeft->rev(50);
  //     motorRight->rev(50);
  //   }

  // }else{
  //   if((error[1] - time1) > 3500){
  //     motorLeft->fwd(powerLeft);
  //     motorRight->fwd(powerRight);
  //   } else {
  //     motorLeft->fwd(50);
  //     motorRight->fwd(50);
  //   }
  // }
}

void moveAllpidGyroNew(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, long gyroValue, long *powerRightL, float valueRef)
{
  float powerLeft;
  float powerRight;

  float lastT = error[1];
  float lastE = error[0];
  float deltaT;

  // float valueRef = 0;
  /*if(gyroValue <= 12 && gyroValue >= -12)
  {
    gyroValue = 0;
  }*/

  error[0] = (gyroValue - valueRef); // - giro; // diferença entre os encoderes sendo o error atual
  error[1] = millis();
  // Serial.println(error[0]);

  deltaT = (error[1] - lastT) / 1000;

  *soma = (*soma) * 0.6 + error[0] * deltaT;

  if ((*soma) * ki > 10)
  {
    *soma = 10 / ki;
  }
  else if ((*soma) * ki < -10)
  {
    *soma = -10 / ki;
  }

  powerLeft = abs(_power);
  powerRight = abs((*powerRightL)) + (error[0] * kp) + (*soma) * ki;
  // Serial.println("LEFT");
  // Serial.println(powerLeft);
  // Serial.println("right");
  // Serial.println(powerRight);

  powerLeft = (powerLeft > 255) ? 255 : powerLeft;
  powerRight = (powerRight > 255) ? 255 : powerRight;
  powerLeft = (powerLeft < 0) ? 0 : powerLeft;
  powerRight = (powerRight < 0) ? 0 : powerRight;

  motorLeft->fwd(powerLeft);
  motorRight->fwd(powerRight);
  *powerRightL = powerRight;

  // Quando a potência era negativa, adotamos que o robô andaria para trás
  if (_power < 0)
  {

    if ((error[1] - time1) > 3500)
    {
      motorLeft->rev(powerLeft);
      motorRight->rev(powerRight);
    }
    else
    {
      motorLeft->rev(50);
      motorRight->rev(50);
    }
  }
  else
  {
    if ((error[1] - time1) > 3500)
    {
      motorLeft->fwd(powerLeft);
      motorRight->fwd(powerRight);
    }
    else
    {
      motorLeft->fwd(50);
      motorRight->fwd(50);
    }
  }
}