#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000  // Definindo o tamanho do array para 100.000 elementos

// Função para Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Função para Bubble Sort com otimização
void bubbleSort(int arr[], int n) {
    int swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;  // Se não houve troca, o array já está ordenado
    }
}

// Função para Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Troca os valores sem o uso de variável temporária extra
        arr[i] ^= arr[min_idx];
        arr[min_idx] ^= arr[i];
        arr[i] ^= arr[min_idx];
    }
}

// Funções auxiliares para Merge Sort
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Funções auxiliares para Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[low + (high - low) / 2];  // Mudança no pivô para ser o elemento do meio
    int i = low - 1, j = high + 1;
    while (1) {
        do i++; while (arr[i] < pivot);
        do j--; while (arr[j] > pivot);
        if (i >= j) return j;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi);
        quickSort(arr, pi + 1, high);
    }
}

// Funções auxiliares para Heap Sort
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;

    if (largest != i) {
        arr[i] ^= arr[largest];
        arr[largest] ^= arr[i];
        arr[i] ^= arr[largest];
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
        arr[0] ^= arr[i];
        arr[i] ^= arr[0];
        arr[0] ^= arr[i];
        heapify(arr, i, 0);
    }
}

// Função para medir o tempo de execução de algoritmos
void measureExecutionTime(void (*sortFunction)(int[], int), int arr[], int n, const char* sortName) {
    int* arrCopy = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];

    clock_t start = clock();
    sortFunction(arrCopy, n);
    clock_t end = clock();

    double executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução do %s para %d elementos: %f segundos\n", sortName, n, executionTime);
    free(arrCopy);
}

void measureExecutionTimeRange(void (*sortFunction)(int[], int, int), int arr[], int n, const char* sortName) {
    int* arrCopy = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) arrCopy[i] = arr[i];

    clock_t start = clock();
    sortFunction(arrCopy, 0, n - 1);
    clock_t end = clock();

    double executionTime = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Tempo de execução do %s para %d elementos: %f segundos\n", sortName, n, executionTime);
    free(arrCopy);
}

// Função principal
int main() {
    int arr[SIZE];
    srand(time(0));
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000000;
    }

    // Medindo o tempo de execução de cada algoritmo
    measureExecutionTime(insertionSort, arr, SIZE, "Insertion Sort");
    measureExecutionTime(bubbleSort, arr, SIZE, "Bubble Sort");
    measureExecutionTime(selectionSort, arr, SIZE, "Selection Sort");
    measureExecutionTimeRange(mergeSort, arr, SIZE, "Merge Sort");
    measureExecutionTimeRange(quickSort, arr, SIZE, "Quick Sort");
    measureExecutionTime(heapSort, arr, SIZE, "Heap Sort");

    return 0;
}
