#include <Arduino.h>
#include <MotorDC.h>
#include <SensorColor.h>
#include <Ultrasonic.h>
#include <Move.h>
#include <Gyro.h>
#include <MPU6050.h>
#include <I2Cdev.h>


// Motor Direita
#define pin1A 5
#define pin1B 6
#define pin1pwm 7
#define pin1Enc A0

// Motor Esquerda
#define pin2A 8
#define pin2B 9
#define pin2pwm 10
#define pin2Enc A1

//Ultrassom Frente
#define pinFrontTrigger 52
#define pinFrontEcho 53

//Ultrassom Esquerda
#define pinLeftTrigger 50
#define pinLeftEcho 51

//Ultrassom Direita
#define pinRightTrigger 48
#define pinRightEcho 49

// Sensor de cor esquerda
#define pinColorLeftS0 44
#define pinColorLeftS1 45
#define pinColorLeftS2 46
#define pinColorLeftS3 47
#define pinColorLeftOut 43


#define EIXO_X 0
#define EIXO_Y 1
#define EIXO_Z 2

int firstReading = true;

MPU6050 accelgyro;
I2Cdev   I2C_M;

MotorDC motorRight (5, 7, 8, 18); 
MotorDC motorLeft (6, 4, 9, 2);

Ultrasonic SensorUltraFront(pinFrontTrigger, pinFrontEcho);
Ultrasonic SensorUltraLeft(pinLeftTrigger, pinLeftEcho);
Ultrasonic SensorUltraRight(pinRightTrigger, pinRightEcho);

SensorColor SensorColorLeft(pinColorLeftS0, pinColorLeftS1, pinColorLeftS2, pinColorLeftS3, pinColorLeftOut);

Gyro gyroscope;

//Declaração de variáveis que serão parâmetros na função moveAllpid.
float soma = 0;
float error [2];
float giro = 0;
float mR;
float mL;
unsigned long tsart;
long powerRightL = 60;

uint8_t buffer_m[6];
int16_t ax, ay, az;
int16_t gx, gy, gz;
int16_t   mx, my, mz;
float heading;
float tiltheading;

float Axyz[3];
float Gxyz[3];
float Mxyz[3];

#define sample_num_mdate  5000

volatile float mx_sample[3];
volatile float my_sample[3];
volatile float mz_sample[3];

static float mx_centre = 0;
static float my_centre = 0;
static float mz_centre = 0;

volatile int mx_max = 0;
volatile int my_max = 0;
volatile int mz_max = 0;

volatile int mx_min = 0;
volatile int my_min = 0;
volatile int mz_min = 0;


void inc (){

  motorLeft.encSignal();
  
}

void incR (){

	motorRight.encSignal();
}

void getAccel_Data();
void Mxyz_init_calibrated();
void getGyro_Data();
void getCompassDate_calibrated();
void get_calibration_Data();
void get_one_sample_date_mxyz();
void getCompass_Data();

void setup() {
	tsart = millis();
  	Serial.begin(9600);
  	attachInterrupt(digitalPinToInterrupt(2), inc, RISING);
	attachInterrupt(digitalPinToInterrupt(18), incR, RISING);
  	error[0] = 0;
	error[1] = millis();
	Wire.begin();
   // Wire.beginTransmission(0x68);  //Inicia transmissão para o endereço do MPU
   // Wire.write(0x6B);
   // Wire.write(0); 
   // Wire.endTransmission(true);
   accelgyro.initialize();

//    Mxyz_init_calibrated(); //para calibrar
}


void loop() {

	while(millis()- tsart < 5000){	

	}
	/*
	long angular = ((gyroscope.filter(1, EIXO_Z)));
	Serial.print("eixo z:");
	Serial.print(angular);
	Serial.print("\n");
	*/
	getAccel_Data();
    getGyro_Data();
	getCompassDate_calibrated();
	if (firstReading){
		float valueRef = Mxyz[1];
		firstReading = false;
	}
	
	//moveAllpidGyro(80, &motorLeft, &motorRight, &soma, error, angular, &powerRightL, valueRef);
	Serial.println("Compass Value of X,Y,Z:");
    Serial.print(Mxyz[0]);
    Serial.print(",");
    Serial.print(Mxyz[1]);
    Serial.print(",");
    Serial.println(Mxyz[2]);
	// Serial.println("Acceleration(g) of X,Y,Z:");
    // Serial.print(Axyz[0]);
    // Serial.print(",");
    // Serial.print(Axyz[1]);
    // Serial.print(",");
    // Serial.println(Axyz[2]);

	delay(2500); 

  
  

	// turnDegrees(60, 90, HORARIO, &motorLeft, &motorRight);
  	// FowardCm(80, 1800, &motorLeft, &motorRight, &soma, error, angular, &powerRightL);
  	//moveAllpidGyro(80, &motorLeft, &motorRight, &soma, error, angular, &powerRightL);
	
	// Serial.print("Esquerda: ");verme pret laranj amarel
	// Serial.println(motorLeft.getCount());
	// Serial.print("Direita: ");
	// Serial.println(motorRight.getCount());

  
}

void Mxyz_init_calibrated() {

    Serial.println(F("Before using 9DOF,we need to calibrate the compass frist,It will takes about 2 minutes."));
    Serial.print("  ");
    Serial.println(F("During  calibratting ,you should rotate and turn the 9DOF all the time within 2 minutes."));
    Serial.print("  ");
    Serial.println(F("If you are ready ,please sent a command data 'ready' to start sample and calibrate."));
    while (!Serial.find("ready"));
    Serial.println("  ");
    Serial.println("ready");
    Serial.println("Sample starting......");
    Serial.println("waiting ......");

    get_calibration_Data();

    Serial.println("     ");
    Serial.println("compass calibration parameter ");
    Serial.print(mx_centre);
    Serial.print("     ");
    Serial.print(my_centre);
    Serial.print("     ");
    Serial.println(mz_centre);
    Serial.println("    ");
}


void get_calibration_Data() {
    for (int i = 0; i < sample_num_mdate; i++) {
        get_one_sample_date_mxyz();
        /*
            Serial.print(mx_sample[2]);
            Serial.print(" ");
            Serial.print(my_sample[2]);                            //you can see the sample data here .
            Serial.print(" ");
            Serial.println(mz_sample[2]);
        */



        if (mx_sample[2] >= mx_sample[1]) {
            mx_sample[1] = mx_sample[2];
        }
        if (my_sample[2] >= my_sample[1]) {
            my_sample[1] = my_sample[2];    //find max value
        }
        if (mz_sample[2] >= mz_sample[1]) {
            mz_sample[1] = mz_sample[2];
        }

        if (mx_sample[2] <= mx_sample[0]) {
            mx_sample[0] = mx_sample[2];
        }
        if (my_sample[2] <= my_sample[0]) {
            my_sample[0] = my_sample[2];    //find min value
        }
        if (mz_sample[2] <= mz_sample[0]) {
            mz_sample[0] = mz_sample[2];
        }

    }

    mx_max = mx_sample[1];
    my_max = my_sample[1];
    mz_max = mz_sample[1];

    mx_min = mx_sample[0];
    my_min = my_sample[0];
    mz_min = mz_sample[0];



    mx_centre = (mx_max + mx_min) / 2;
    my_centre = (my_max + my_min) / 2;
    mz_centre = (mz_max + mz_min) / 2;

}






void get_one_sample_date_mxyz() {
    getCompass_Data();
    mx_sample[2] = Mxyz[0];
    my_sample[2] = Mxyz[1];
    mz_sample[2] = Mxyz[2];
}


void getAccel_Data(void) {
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Axyz[0] = (double) ax / 16384;
    Axyz[1] = (double) ay / 16384;
    Axyz[2] = (double) az / 16384;
}

void getGyro_Data(void) {
    accelgyro.getMotion9(&ax, &ay, &az, &gx, &gy, &gz, &mx, &my, &mz);
    Gxyz[0] = (double) gx * 250 / 32768;
    Gxyz[1] = (double) gy * 250 / 32768;
    Gxyz[2] = (double) gz * 250 / 32768;
}

void getCompass_Data(void) {
    I2C_M.writeByte(MPU9150_RA_MAG_ADDRESS, 0x0A, 0x01); //enable the magnetometer
    delay(10);
    I2C_M.readBytes(MPU9150_RA_MAG_ADDRESS, MPU9150_RA_MAG_XOUT_L, 6, buffer_m);

    mx = ((int16_t)(buffer_m[1]) << 8) | buffer_m[0] ;
    my = ((int16_t)(buffer_m[3]) << 8) | buffer_m[2] ;
    mz = ((int16_t)(buffer_m[5]) << 8) | buffer_m[4] ;

    Mxyz[0] = (double) mx * 1200 / 4096;
    Mxyz[1] = (double) my * 1200 / 4096;
    Mxyz[2] = (double) mz * 1200 / 4096;
}

void getCompassDate_calibrated() {
    getCompass_Data();
    Mxyz[0] = Mxyz[0] - mx_centre;
    Mxyz[1] = Mxyz[1] - my_centre;
    Mxyz[2] = Mxyz[2] - mz_centre;
}