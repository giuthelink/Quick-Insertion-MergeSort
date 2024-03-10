#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Função para imprimir o array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Implementação do InsertionSort
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Implementação do QuickSort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Implementação do MergeSort
void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main() {
    srand(time(NULL));

    int sizes[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000};

    for (int i = 0; i < sizeof(sizes) / sizeof(sizes[0]); i++) {
        int size = sizes[i];
        int arr[size], arr_copy[size];

        // Preencher o array com números aleatórios
        for (int j = 0; j < size; j++) {
            arr[j] = rand();
        }

        // Copiar o array para preservar a ordem original para comparação
        for (int j = 0; j < size; j++) {
            arr_copy[j] = arr[j];
        }

        // Medir o tempo de execução para o InsertionSort
        clock_t start_time = clock();
        insertionSort(arr, size);
        clock_t end_time = clock();
        double insertion_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        // Restaurar o array original
        for (int j = 0; j < size; j++) {
            arr[j] = arr_copy[j];
        }

        // Medir o tempo de execução para o QuickSort
        start_time = clock();
        quickSort(arr, 0, size - 1);
        end_time = clock();
        double quicksort_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        // Restaurar o array original
        for (int j = 0; j < size; j++) {
            arr[j] = arr_copy[j];
        }

        // Medir o tempo de execução para o MergeSort
        start_time = clock();
        mergeSort(arr, 0, size - 1);
        end_time = clock();
        double mergesort_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

        // Imprimir resultados
        printf("Tamanho do array: %d\n", size);
        printf("InsertionSort: %.6f segundos\n", insertion_time);
        printf("QuickSort: %.6f segundos\n", quicksort_time);
        printf("MergeSort: %.6f segundos\n", mergesort_time);
        printf("\n");
    }

    return 0;
}
