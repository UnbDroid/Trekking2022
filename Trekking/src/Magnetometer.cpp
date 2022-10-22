#include "Magnetometer.h"

void HMC5883_Start()
{
    SDA = 1;
    SCL = 1;
    Delay5us();
    SDA = 0;
    Delay5us();
    SCL = 0;
}