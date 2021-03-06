#include <Arduino.h>
#include <Move.h>
#include <math.h>

#define kp 0.05
#define ki 0.0075


/*Encoder

#define kp 0.2
#define ki 0.001

*/
float time1 = millis();


//Função que move as duas rodas para a frente.
void moveAll(int _power, MotorDC *motorLeft, MotorDC *motorRight) {
  motorLeft->fwd(_power);
  motorRight->fwd(_power);
  // motorRight->fwd(_power-35);
}


//Função que move as duas para frente, porém usando o PID.
void moveAllpid(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, float giro, long *powerRightL) {
  float powerLeft;
  float powerRight;

  float lastT = error[1];
  float deltaT;


  float mLeft = motorLeft->getCount();
  float mRight = motorRight->getCount();
  error[0] = (mLeft - mRight);// - giro; // diferença entre os encoderes sendo o error atual
  error[1] = millis();
  Serial.println(error[0]);

  deltaT = (error[1] - lastT)/1000;

  *soma = (*soma)*0.6 + error[0]*deltaT;

  if((*soma)*ki > 10){
    *soma = 10/ki;
  }
  else if((*soma)*ki < -10){
    *soma = -10/ki;
  }

  powerLeft = abs(_power);
  powerRight = abs((*powerRightL)) + (error[0]*kp) + (*soma)*ki;
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

  //Quando a potência era negativa, adotamos que o robô andaria para trás
  if(_power < 0){

    if((error[1] - time1) > 3500){
      motorLeft->rev(powerLeft);
      motorRight->rev(powerRight);
    } else {
      motorLeft->rev(50);
      motorRight->rev(50);
    }

  }else{
    if((error[1] - time1) > 3500){
      motorLeft->fwd(powerLeft);
      motorRight->fwd(powerRight);
    } else {
      motorLeft->fwd(50);
      motorRight->fwd(50);
    }
  }
}


//Função que move as duas rodas para trás.
void moveRevAll(int _power, MotorDC *motorLeft, MotorDC *motorRight) {
  motorLeft->rev(_power);
  motorRight->rev(_power);
}


//Função que para as duas rodas.
void stopAll(MotorDC *motorLeft, MotorDC *motorRight) {
  motorRight->stop();
  motorLeft->stop();
}


//Função que gira o robô no sentido horário.
void turnClockwise(int _power, MotorDC *motorLeft, MotorDC *motorRight) {
  stopAll(motorLeft, motorRight);
  motorLeft->fwd(_power);
  motorRight->rev(_power);
  delay(120);
  stopAll(motorLeft,motorRight);
}

//Função que gira o robô no sentido antihorário.
void turnAnticlockwise(int _power,  MotorDC *motorLeft, MotorDC *motorRight) {
  stopAll(motorLeft, motorRight);
  motorRight->fwd(_power);
  motorLeft->rev(_power);
  delay(120);
  stopAll(motorLeft,motorRight);
}

//Função que gira o robô de acordo com o graus.
//dir = HORARIO ou ANTIHORARIO
void turnDegrees(int _power, int _degree, int _clock, MotorDC *motorLeft, MotorDC *motorRight) {
  int c = DIAMETER*3.14;
  //Perimetro que a roda deve andar para chegar na quantidade de graus desejada
  int move = (GIRO*(WDIST*3.14*2)*((float) _degree/360))/c;

  //Variáveis que armazenam as contagens dos encoderes
  int countLeftInitial = motorLeft->getCount();
  int countLeftUpdate = motorLeft->getCount();
  int countRightInitial = motorRight->getCount();
  int countRightUpdate = motorRight->getCount();

  //Girar sentido horário
  if (_clock == HORARIO) {
    motorLeft->fwd(_power);
    motorRight->rev(_power);
    //Enquanto distância entre o enconder atual e o inicial não for o desejado (MOVE) ele vai continuar girando.
    while((countLeftUpdate - countLeftInitial) < move ) {
      countLeftUpdate = motorLeft->getCount();
      Serial.println("Counter L deg");
      Serial.println(countLeftUpdate);
    }
    //Quando a distância do enconder atual e o inicial for igual o desejado (MOVE), o robô tem que parar de girar.
    stopAll(motorLeft, motorRight);
  }

  else if (_clock == ANTIHORARIO) {
    motorRight->fwd(_power);
    motorLeft->rev(_power);
    while((countRightUpdate - countRightInitial) < move) {
      countRightUpdate = motorRight->getCount();
      Serial.println("Counter R");
      Serial.println(countRightUpdate);
    }
    stopAll(motorLeft, motorRight);
  }
  else {
    //error
  }
  stopAll(motorLeft, motorRight);
}

//Andar para frente uma certa distância.
void FowardCm(int _power, long _distance, MotorDC *motorLeft, MotorDC *motorRight, float *soma,float *error, long gyroValue,long *powerRightL) {
  // ------------------------------------------------------------------------------------------------
  // A funcao moveAllpidGyro nao funciona quando chama aqui dentro, ai pra testar a gente
  // mudou na moveAll para o direito andar com _power-30
  // E nao mudamos o valor de GIRO, ai por isso ta andando um pouco mais do que o valor especificado,
  // tem que ver um jeito melhor de medir o GIRO
  // ------------------------------------------------------------------------------------------------

  int countLeftInitial = motorLeft->getCount();
  int countLeftUpdate = motorLeft->getCount();
  long c = DIAMETER*PI;
  long move = (_distance*GIRO)/c;

  moveAll(_power, motorLeft, motorRight);
  // moveAllpidGyro(_power, motorLeft, motorRight, soma, error, gyroValue, powerRightL);

//Enquanto distância entre o enconder atual e o inicial não for o desejado (MOVE) ele vai continuar andando pra frente.
  while((countLeftUpdate - countLeftInitial) < move ) {
    moveAll(_power, motorLeft, motorRight);
    // moveAllpidGyro(_power, motorLeft, motorRight, soma, error, gyroValue, powerRightL);
    countLeftUpdate = motorLeft->getCount();
  }
  stopAll(motorLeft, motorRight);
}


//Andar para trás uma certa distância
void RevCm(int _power, int _distance, MotorDC *motorLeft, MotorDC *motorRight) {
  int countLeft = 0;
  int c = DIAMETER*PI;
  int move = (_distance*GIRO)/c;

  moveRevAll(_power, motorLeft, motorRight);

  while(countLeft < move) {
    countLeft = motorLeft->getCount();
  }

  stopAll(motorLeft, motorRight);
}



void moveAllpidGyro(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, long gyroValue, long *powerRightL, int valueRef, unsigned long *tPrint) {
  float powerLeft;
  float powerRight;


  float lastT = error[1];
  float lastE = error[0];
  float deltaT;


  // float valueRef = 0;
  // if(gyroValue <= 125 && gyroValue >= 80)
  // {
  //   gyroValue = 0;
  // }
  
  error[0] = (gyroValue - valueRef);// - giro; // diferença entre os encoderes sendo o error atual
  error[1] = millis();
  // Serial.println(error[0]);

  deltaT = (error[1] - lastT)/1000;

  *soma = (*soma)*0.6 + error[0]*deltaT;

  if((*soma)*ki > 10){
    *soma = 10/ki;
  }
  else if((*soma)*ki < -10){
    *soma = -10/ki;
  }

  powerLeft = abs(_power);
  powerRight = abs((*powerRightL)) + (error[0]*kp);// + (*soma)*ki;

  if(millis() - *tPrint > 100) {
      *tPrint = millis();
      if(error[0] > 0){
        Serial.println("LEFT");
      } else {
        Serial.println("RIGHT");
      }

      // Serial.println();
      // Serial.println("LEFT");
      // Serial.println(powerLeft);
      // Serial.println("right");
      // Serial.println(powerRight);
      }

  powerLeft = (powerLeft > 255) ? 255 : powerLeft;
  powerRight = (powerRight > 255) ? 255 : powerRight;
  powerLeft = (powerLeft < 0) ? 0 : powerLeft;
  powerRight = (powerRight < 0) ? 0 : powerRight;

  motorLeft->fwd(powerLeft);
  motorRight->fwd(powerRight);
  *powerRightL = powerRight;

  //Quando a potência era negativa, adotamos que o robô andaria para trás
  if(_power < 0){

    if((error[1] - time1) > 3500){
      motorLeft->rev(powerLeft);
      motorRight->rev(powerRight);
    } else {
      motorLeft->rev(50);
      motorRight->rev(50);
    }

  }else{
    if((error[1] - time1) > 3500){
      motorLeft->fwd(powerLeft);
      motorRight->fwd(powerRight);
    } else {
      motorLeft->fwd(50);
      motorRight->fwd(50);
    }
  }
}


void moveAllpidGyroNew(int _power, MotorDC *motorLeft, MotorDC *motorRight, float *soma, float *error, long gyroValue, long *powerRightL, float valueRef) {
  float powerLeft;
  float powerRight;

  float lastT = error[1];
  float lastE = error[0];
  float deltaT;


  //float valueRef = 0;
  /*if(gyroValue <= 12 && gyroValue >= -12)
  {
    gyroValue = 0;
  }*/

  error[0] = (gyroValue - valueRef);// - giro; // diferença entre os encoderes sendo o error atual
  error[1] = millis();
  // Serial.println(error[0]);

  deltaT = (error[1] - lastT)/1000;

  *soma = (*soma)*0.6 + error[0]*deltaT;

  if((*soma)*ki > 10){
    *soma = 10/ki;
  }
  else if((*soma)*ki < -10){
    *soma = -10/ki;
  }

  powerLeft = abs(_power);
  powerRight = abs((*powerRightL)) + (error[0]*kp) + (*soma)*ki;
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

  //Quando a potência era negativa, adotamos que o robô andaria para trás
  if(_power < 0){

    if((error[1] - time1) > 3500){
      motorLeft->rev(powerLeft);
      motorRight->rev(powerRight);
    } else {
      motorLeft->rev(50);
      motorRight->rev(50);
    }

  }else{
    if((error[1] - time1) > 3500){
      motorLeft->fwd(powerLeft);
      motorRight->fwd(powerRight);
    } else {
      motorLeft->fwd(50);
      motorRight->fwd(50);
    }
  }
}