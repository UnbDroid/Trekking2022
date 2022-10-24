#include <UltrasonicFilter.h>
#include <ColorSensor.h>

UltrasonicFilter::UltrasonicFilter() {}

// Swap two elements - Utility function
void UltrasonicFilter::swap(float *a, float *b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

int UltrasonicFilter::partition(float arr[], int start, int end)
{

    float pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(&(arr[pivotIndex]), &(arr[start]));

    // Sorting left and right parts of the pivot element
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (arr[i] <= pivot)
        {
            i++;
        }

        while (arr[j] > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(&(arr[i++]), &(arr[j--]));
        }
    }

    return pivotIndex;
}

void UltrasonicFilter::quickSort(float arr[], int start, int end)
{

    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(arr, start, end);

    // Sorting the left part
    quickSort(arr, start, p - 1);

    // Sorting the right part
    quickSort(arr, p + 1, end);
}

void UltrasonicFilter::filter(Ultrasonic ultrasonic)
{
    float values[NUM_OF_READINGS];

    // le os valores do ultrassom
    for (int i = 0; i < NUM_OF_READINGS; i++)
    {
        long auxValue = ultrasonic.timing();
        values[i] = ultrasonic.convert(auxValue, Ultrasonic::CM);
    }

    // ordena o vetor de leituras
    quickSort(values, 0, NUM_OF_READINGS - 1);

    // pega os valores do meio do vetor e bota no retorno
    // com os valores atuais das constantes ele retorna os 3 valores do meio do vetor ordenado
    int j = 0;
    for (int i = (NUM_OF_READINGS / 2) - NUM_OF_SPREAD_INTERVAL_SAMPLES; i <= (NUM_OF_READINGS / 2) + NUM_OF_SPREAD_INTERVAL_SAMPLES; i++)
    {
        if (values[i] < 0)
            values[i] = 0;

        this->results[j] = values[i] < 100 ? values[i] : 100;
        j++;
    }
}

void UltrasonicFilter::printArray(float values[])
{
    for (int i = 0; i < NUM_OF_RESULTS; i++)
    {
        Serial.print(values[i]);
        Serial.print(" ");
    }
    Serial.println();
}