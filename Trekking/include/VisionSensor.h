#ifndef VISIONSENSOR_H
#define VISIONSENSOR_H

#include "defines.h"

class VisionSensor
{
    private:
        int m_lastReading = 0;
        int m_pinStart;

    public:
        /* Sensor de Visao
        Descricao: Construtor da Classe.
            Parâmetros:
            - _pinStart: Primeiro pino da visão (incremento dois a dois).
        */
        VisionSensor(int _pinStart);
        int getAngle();
        int getFilteredAngle();
};

#endif