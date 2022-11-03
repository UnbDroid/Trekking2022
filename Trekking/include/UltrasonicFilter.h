#ifndef ULTRASONICFILTER_H
#define ULTRASONICFILTER_H

#include <Arduino.h>
#include <Ultrasonic.h>

static const int NUM_OF_READINGS = 5;                                       // numero de leituras do ultrassom
static const int NUM_OF_SPREAD_INTERVAL_SAMPLES = 1;                        // valor usado para definir quantos valores filtrados serão retornados
static const int NUM_OF_RESULTS = (2 * NUM_OF_SPREAD_INTERVAL_SAMPLES) + 1; // quantidade de valores filtrados retornados

void swap(float *a, float *b);
int partition(float arr[], int start, int end);
void quickSort(float arr[], int start, int end);

static float filtered_values1[NUM_OF_READINGS] = {100, 100, 100, 100, 100};
static float filtered_values2[NUM_OF_READINGS] = {100, 100, 100, 100, 100};
static float filtered_values3[NUM_OF_READINGS] = {100, 100, 100, 100, 100};

static float sorted_values1[NUM_OF_READINGS] = {100, 100, 100, 100, 100};
static float sorted_values2[NUM_OF_READINGS] = {100, 100, 100, 100, 100};
static float sorted_values3[NUM_OF_READINGS] = {100, 100, 100, 100, 100};

static int filter_index = 0;

float *filter(Ultrasonic ultrasonic1, Ultrasonic ultrasonic2, Ultrasonic ultrasonic3);
void printArray(float values[]);

#endif