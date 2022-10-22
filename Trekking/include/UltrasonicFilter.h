#ifndef ULTRASONICFILTER_H
#define ULTRASONICFILTER_H

#include <Arduino.h>
#include <Ultrasonic.h>

class UltrasonicFilter
{
private:
    static const int NUM_OF_READINGS = 10; // numero de leituras do ultrassom
    static const int NUM_OF_SAMPLES = 1; // valor usado para definir quantos valores filtrados serão retornados
    static const int NUM_OF_RESULTS = (2 * NUM_OF_SAMPLES) + 1; // quantidade de valores filtrados retornados
    
    void swap(float* a, float* b);
    int partition(float arr[], int start, int end);
    void quickSort(float arr[], int start, int end);

public:
    float results[NUM_OF_RESULTS];

    UltrasonicFilter();

    void filter(Ultrasonic ultrassonic);
    void printArray(float values[]);
};

#endif