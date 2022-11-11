#include <UltrasonicFilter.h>

// Swap two elements - Utility function
void swap(float *a, float *b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

int partition(float arr[], int start, int end)
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

void quickSort(float arr[], int start, int end)
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

float *filter(Ultrasonic ultrasonic1, Ultrasonic ultrasonic2, Ultrasonic ultrasonic3)
{
    static float result[3];

    // Leitura dos ultrassons e salvando nos vetores
    long auxValue = ultrasonic1.timing();
    float auxReading1 = ultrasonic1.convert(auxValue, Ultrasonic::CM);
    auxReading1 = auxReading1 > 100 ? 100 : auxReading1;
    auxReading1 = auxReading1 < 0 ? 0 : auxReading1;
    filtered_values1[filter_index] = auxReading1;

    long auxValue2 = ultrasonic2.timing();
    float auxReading2 = ultrasonic2.convert(auxValue2, Ultrasonic::CM);
    auxReading2 = auxReading2 > 100 ? 100 : auxReading2;
    auxReading2 = auxReading2 < 0 ? 0 : auxReading2;
    filtered_values2[filter_index] = auxReading2;

    long auxValue3 = ultrasonic3.timing();
    float auxReading3 = ultrasonic3.convert(auxValue3, Ultrasonic::CM);
    auxReading3 = auxReading3 > 100 ? 100 : auxReading3;
    auxReading3 = auxReading3 < 0 ? 0 : auxReading3;
    filtered_values3[filter_index] = auxReading3;

    // Atualiza o indice para a media movel
    filter_index = (filter_index + 1) % NUM_OF_READINGS;

    // Passando os valores para o vetor que sera ordenado
    for (int i = 0; i < NUM_OF_READINGS; i++)
    {
        sorted_values1[i] = filtered_values1[i];
        sorted_values2[i] = filtered_values2[i];
        sorted_values3[i] = filtered_values3[i];
    }

    // Ordenando os vetores
    quickSort(sorted_values1, 0, NUM_OF_READINGS - 1);
    quickSort(sorted_values2, 0, NUM_OF_READINGS - 1);
    quickSort(sorted_values3, 0, NUM_OF_READINGS - 1);

    // Retorna um valor do meio dos vetores ordenados
    result[0] = sorted_values1[2];
    result[1] = sorted_values2[2];
    result[2] = sorted_values3[2];

    return result;

    // float filtered_values[NUM_OF_RESULTS];
    // float values[NUM_OF_READINGS];

    // // le os valores do ultrassom

    // for (int i = 0; i < NUM_OF_READINGS; i++)
    // {
    //     long auxValue = ultrasonic.timing();
    //     values[i] = ultrasonic.convert(auxValue, Ultrasonic::CM);
    // }

    // // ordena o vetor de leituras
    // quickSort(values, 0, NUM_OF_READINGS - 1);

    // // pega os valores do meio do vetor e bota no retorno
    // // com os valores atuais das constantes ele retorna os 3 valores do meio do vetor ordenado
    // int j = 0;
    // for (int i = (NUM_OF_READINGS / 2) - NUM_OF_SPREAD_INTERVAL_SAMPLES; i <= (NUM_OF_READINGS / 2) + NUM_OF_SPREAD_INTERVAL_SAMPLES; i++)
    // {
    //     filtered_values[j] = values[i] > 0 ? values[i] : 0;
    //     filtered_values[j] = values[i] < 100 ? values[i] : 100;
    //     j++;
    // }
    // return filtered_values[0];
}
