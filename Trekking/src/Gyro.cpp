#include<Gyro.h>
 
//Endereco I2C do MPU6050
const int MPU=0x68;  //pino aberto 0X68 , pino ligado em 3,3V 0x69

int data[7];

Gyro::Gyro(){
    
}

Gyro::~Gyro(){}
 

long Gyro::requestData(int valorEixo){
  Wire.beginTransmission(MPU);      //transmite
  Wire.write(0x3B);                 // Endereço 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);     //Finaliza transmissão
  
  Wire.requestFrom(MPU,14,true);

  for(int i = 0; i <= 6; i++){
      data[i] = Wire.read()<<8|Wire.read();
  }

    return data[valorEixo];

}

long Gyro::filter(int count, int eixoValue){
	int i = 0;
	long eixo = 0;
	while (i < count){
		 eixo =+ this->requestData(eixoValue);
		i++;
	}
    return (eixo)/count;
}
