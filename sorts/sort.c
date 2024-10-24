#include "sort.h"
#include <stdbool.h>
#include <stdio.h>

// Protocolo das Funções
void bubblesort_aprimorado(int v[], int n);
void quicksort(int v[], int inf, int sup);
void selectionSort(int arr[], int n);
void insertionSort(int arr[], int n);
void shellSort(int arr[], int n);
void countingSmaller(int arr[], int n);

void merge(int arr[], int l, int m, int r);
void mergeSort(int arr[], int l, int r);

void heapify(int arr[], int n, int i);
void heapSort(int arr[], int n);

int getMax(int arr[], int n);
void countingSortForRadix(int arr[], int n, int exp);
void radixSort(int arr[], int n);

// BubbleSort
void bubblesort_aprimorado(int v[], int n) {
  int i, j, aux, troca = 1;
  for (i = 0; i < n && troca; i++) {
    troca = 0;
    for (j = 0; j < n - i - 1; j++)
      if (v[j] > v[j + 1]) {
        troca = 1;
        aux = v[j];
        v[j] = v[j + 1];
        v[j + 1] = aux;
      }
  }
}

// QuickSort
void quicksort(int v[], int inf, int sup) {
  int aux;
  int meio = (inf + sup) / 2; // Índice do pivô
  int pivo = v[meio];         // Pivô é o elemento do meio
  int i = inf;                // Índice do início
  int j = sup;                // Índice do final

  do {
    while (v[i] < pivo)
      i++; // Encontra o primeiro elemento maior ou igual ao pivô
    while (v[j] > pivo)
      j--;        // Encontra o primeiro elemento menor ou igual ao pivô
    if (i <= j) { // Se i é menor ou igual a j, faz a troca
      aux = v[i];
      v[i] = v[j];
      v[j] = aux;
      i++;
      j--;
    }
  } while (i <= j);

  // Chamadas recursivas
  if (j > inf)
    quicksort(v, inf, j);
  if (i < sup)
    quicksort(v, i, sup);

  /* Complexidade:
- Tempo: O(n^2) no pior caso (caso já esteja ordenado); O(n log n) no melhor e
médio caso
- Espaço: O(log n) na média para a pilha de chamadas (pode ser O(n) no pior
caso)
*/
}

// SelectionSort
void selectionSort(int arr[], int n) {
  for (int i = 0; i < n - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < n; j++)
      if (arr[j] < arr[min_idx])
        min_idx = j;

    int temp = arr[min_idx];
    arr[min_idx] = arr[i];
    arr[i] = temp;
  }

  /* Complexidade:
 - Tempo: O(n^2) em todos os casos (melhor, médio e pior)
 - Espaço: O(1) (ordenado in-place)
*/
}

// Função do InsertionSort
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

  /* Complexidade:
 - Tempo: O(n^2) no pior caso; O(n) no melhor caso (quando a lista já está
 ordenada)
 - Espaço: O(1) (ordenado in-place)
*/
}

// Função do ShellSort
void shellSort(int arr[], int n) {
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i++) {
      int temp = arr[i];
      int j;
      for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
        arr[j] = arr[j - gap];
      arr[j] = temp;
    }
  }

  /* Complexidade:
 - Tempo: O(n^2) no pior caso; O(n log n) na maioria dos casos práticos
 (dependendo da escolha de gaps)
 - Espaço: O(1) (ordenado in-place)
*/
}

// Função do Contagem de Menores
void countingSmaller(int arr[], int n) {
  int output[n];
  for (int i = 0; i < n; i++) {
    output[i] = 0;
    for (int j = 0; j < n; j++) {
      if (arr[j] < arr[i])
        output[i]++;
    }
  }

  for (int i = 0; i < n; i++)
    arr[i] = output[i];
}

// Funções para o MergeSort

// Função de merge(mesclar)
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

// MergeSort em si
void mergeSort(int arr[], int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);
    merge(arr, l, m, r);
  }

  /* Complexidade:
 - Tempo: O(n log n) em todos os casos
 - Espaço: O(n) (não é in-place devido à necessidade de arrays temporários)
*/
}

// Funções para o HeapSort

// Função para a criação da árvore binária e seu rearranjo
void heapify(int arr[], int n, int i) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left] > arr[largest])
    largest = left;

  if (right < n && arr[right] > arr[largest])
    largest = right;

  if (largest != i) {
    int temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;
    heapify(arr, n, largest);
  }
}

// HeapSort em si que utiliza do rearranjo do 'heapify' para ordenar
void heapSort(int arr[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  for (int i = n - 1; i > 0; i--) {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    heapify(arr, i, 0);
  }

  /* Complexidade:
 - Tempo: O(n log n) em todos os casos
 - Espaço: O(1) (ordenado in-place)
*/
}

// Funções para o RadixSort

int getMax(int arr[], int n) {
  int max = arr[0];
  for (int i = 1; i < n; i++)
    if (arr[i] > max)
      max = arr[i];
  return max;
}

void countingSortForRadix(int arr[], int n, int exp) {
  int output[n];
  int count[10] = {0};

  for (int i = 0; i < n; i++)
    count[(arr[i] / exp) % 10]++;

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
  }

  for (int i = 0; i < n; i++)
    arr[i] = output[i];
}

void radixSort(int arr[], int n) {
  int max = getMax(arr, n);

  for (int exp = 1; max / exp > 0; exp *= 10)
    countingSortForRadix(arr, n, exp);

  /* Complexidade:
- Tempo: O(nk), onde k é o número de dígitos no maior número
- Espaço: O(n) (para o array de saída)
*/
}
