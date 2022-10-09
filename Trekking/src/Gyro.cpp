#include<Gyro.h>
 
//Endereco I2C do MPU6050
const int MPU=0x68;  //pino aberto 0X68 , pino ligado em 3,3V 0x69

int data[7];

Gyro::Gyro(){
    
}

Gyro::~Gyro(){}
 

double Gyro::requestData(){
    int x, y, z;
    // Indica ao HMC5883 para iniciar a leitura
    Wire.beginTransmission(address);
    Wire.write(0x03); //select register 3, X MSB register
    Wire.endTransmission();

    // Le os dados de cada eixo, 2 registradores por eixo
    Wire.requestFrom(address, 6);
    if(6<=Wire.available())
    {
    x = Wire.read()<<8; //X msb
    x |= Wire.read(); //X lsb
    z = Wire.read()<<8; //Z msb
    z |= Wire.read(); //Z lsb
    y = Wire.read()<<8; //Y msb
    y |= Wire.read(); //Y lsb
    }

    double result = atan2(y,x);

    double gyroValue = result *(180/PI); 
  
    return gyroValue;
}

long Gyro::filter(int count, int eixoValue){
	int i = 0;
	long eixo = 0;
	while (i < count){
		//  eixo =+ this->requestData(eixoValue);
		i++;
	}
    return (eixo)/count;
}
