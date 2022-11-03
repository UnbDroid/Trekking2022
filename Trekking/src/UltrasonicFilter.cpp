#include <UltrasonicFilter.h>
#include <ColorSensor.h>
#include <string.h>

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

float filter(Ultrasonic ultrasonic)
{
    // Leitura dos ultrassons e salvando nos vetores
    long auxValue = ultrasonic.timing();
    filtered_values2[filter_index] = ultrasonic.convert(auxValue, Ultrasonic::CM);

    long auxValue = ultrasonic.timing();
    filtered_values3[filter_index] = ultrasonic.convert(auxValue, Ultrasonic::CM);

    long auxValue = ultrasonic.timing();
    filtered_values4[filter_index] = ultrasonic.convert(auxValue, Ultrasonic::CM);
    filter_index = (filter_index + 1) % 5;

    // Passando os valores para o vetor que sera ordenado
    for (int i = 0; i < 5; i++)
    {
        sorted_values2[i] = filtered_values2[i];
        sorted_values3[i] = filtered_values3[i];
        sorted_values4[i] = filtered_values4[i];
    }

    // Ordenando os vetores
    quickSort(sorted_values2, 0, 4);
    quickSort(sorted_values3, 0, 4);
    quickSort(sorted_values4, 0, 4);

    sorted_values2[2];
    sorted_values3[2];
    sorted_values4[2];
    

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

void printArray(float values[])
{
    char str_values[65];
    // Inicializa a string vazia
    strcpy(str_values, "");
    for (int i = 0; i < NUM_OF_RESULTS; i++)
    {
        char aux[10];
        // Converte o float para string
        sprintf(aux, "%g", values[i]);
        // Concatena os valores na string com um espaço e new line entre eles
        strcat(str_values, aux);
        strcat(str_values, " \n");
    }
    Serial.println(str_values);
}