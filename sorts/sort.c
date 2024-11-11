#include "sort.h"
#include <stdbool.h>
#include <stdio.h>

// Protocolo das Funções
void bubblesort_aprimorado(int v[], int n, int *comparisons, int *movements);
void quicksort(int arr[], int low, int high, int *comparisons, int *movements);
void selectionSort(int arr[], int n, int *comparisons, int *movements);
void insertionSort(int arr[], int n, int *comparisons, int *movements);
void shellSort(int arr[], int n, int *comparisons, int *movements);
void countingSmaller(int arr[], int n, int *comparisons, int *movements);

void merge(int arr[], int l, int m, int r, int *comparisons, int *movements);
void mergeSort(int arr[], int l, int r, int *comparisons, int *movements);

void heapify(int arr[], int n, int i, int *comparisons, int *movements);
void heapSort(int arr[], int n, int *comparisons, int *movements);

void countingSortForRadix(int arr[], int n, int exp, int *comparisons,
                          int *movements);
void radixSort(int arr[], int n, int *comparisons, int *movements);

void swap(int *a, int *b);

// Função do BubbleSort
void bubblesort_aprimorado(int arr[], int n, int *comparisons, int *movements) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      (*comparisons)++;
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
        (*movements)++;
      }
    }
  }
}

// Funções do QuickSort

int medianaDeTres(int arr[], int low, int high) {
  int mid = low + (high - low) / 2;
  if (arr[low] > arr[mid])
    swap(&arr[low], &arr[mid]);
  if (arr[low] > arr[high])
    swap(&arr[low], &arr[high]);
  if (arr[mid] > arr[high])
    swap(&arr[mid], &arr[high]);
  return mid; // Retorna o índice do pivô
}

// Implementação da função swap
void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

void quicksort(int arr[], int low, int high, int *comparisons, int *movements) {
  if (low < high) {
    int pivotIndex = medianaDeTres(arr, low, high);

    // Move o pivô escolhido para o final da partição
    swap(&arr[pivotIndex], &arr[high]);
    (*movements) += 3; // Movimentação do pivô

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
      (*comparisons)++; // Comparação de chaves
      if (arr[j] < pivot) {
        i++;
        swap(&arr[i], &arr[j]);
        (*movements) += 3; // Movimentação do swap
      }
    }
    swap(&arr[i + 1], &arr[high]);
    (*movements) += 3; // Movimentação do swap final

    int pi = i + 1;

    quicksort(arr, low, pi - 1, comparisons, movements);
    quicksort(arr, pi + 1, high, comparisons, movements);
  }

  /* Complexidade:
- Tempo: O(n^2) no pior caso (caso já esteja ordenado); O(n log n) no melhor e
médio caso
- Espaço: O(log n) na média para a pilha de chamadas (pode ser O(n) no pior
caso)
*/
}

// SelectionSort
void selectionSort(int arr[], int n, int *comparisons, int *movements) {
  for (int i = 0; i < n - 1; i++) {
    int min_idx = i;
    for (int j = i + 1; j < n; j++) {
      (*comparisons)++; // Comparação de chaves
      if (arr[j] < arr[min_idx])
        min_idx = j;
    }

    if (min_idx != i) {
      int temp = arr[min_idx];
      arr[min_idx] = arr[i];
      arr[i] = temp;
      (*movements) += 3; // Três movimentações (swap)
    }
  }
  /* Complexidade:
- Tempo: O(n^2) em todos os casos (melhor, médio e pior)
- Espaço: O(1) (ordenado in-place)
*/
}

// Função do InsertionSort
void insertionSort(int arr[], int n, int *comparisons, int *movements) {
  for (int i = 1; i < n; i++) {
    int key = arr[i];
    int j = i - 1;

    (*movements)++; // Movimentação inicial de `key`

    while (j >= 0) {
      (*comparisons)++; // Comparação de chaves
      if (arr[j] > key) {
        arr[j + 1] = arr[j];
        (*movements)++; // Movimentação de elemento
      } else {
        break;
      }
      j--;
    }
    arr[j + 1] = key;
    (*movements)++; // Movimentação final
  }
  /* Complexidade:
- Tempo: O(n^2) no pior caso; O(n) no melhor caso (quando a lista já está
ordenada)
- Espaço: O(1) (ordenado in-place)
*/
}

// Função do ShellSort
void shellSort(int arr[], int n, int *comparisons, int *movements) {
  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i++) {
      int temp = arr[i];
      (*movements)++; // Movimentação inicial de `temp`
      int j;
      for (j = i; j >= gap; j -= gap) {
        (*comparisons)++; // Comparação de chaves
        if (arr[j - gap] > temp) {
          arr[j] = arr[j - gap];
          (*movements)++; // Movimentação de elemento
        } else {
          break;
        }
      }
      arr[j] = temp;
      (*movements)++; // Movimentação final
    }
  }
  /* Complexidade:
- Tempo: O(n^2) no pior caso; O(n log n) na maioria dos casos práticos
(dependendo da escolha de gaps)
- Espaço: O(1) (ordenado in-place)
*/
}

// Função do Contagem de Menores
void countingSmaller(int arr[], int n, int *comparisons, int *movements) {
  int output[n];

  // Inicializa o vetor de contagem com 0
  for (int i = 0; i < n; i++) {
    output[i] = 0;
  }

  // Compara cada elemento com os outros para contar quantos são menores
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      (*comparisons)++;
      if (arr[j] < arr[i]) {
        output[i]++;
      }
    }
  }

  // Atualiza o vetor original com os resultados
  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
    (*movements)++;
  }

  /* Complexidade:
- Tempo: O(n^2) no pior caso
- Espaço: O(n) (vetor auxiliar 'output')
*/
}

// Funções para o MergeSort

// Função de merge(mesclar)
void merge(int arr[], int l, int m, int r, int *comparisons, int *movements) {
  int i, j, k;
  int n1 = m - l + 1;
  int n2 = r - m;

  int L[n1], R[n2];

  for (i = 0; i < n1; i++) {
    L[i] = arr[l + i];
    (*movements)++; // Movimentação para array temporário
  }

  for (j = 0; j < n2; j++) {
    R[j] = arr[m + 1 + j];
    (*movements)++; // Movimentação para array temporário
  }

  i = 0;
  j = 0;
  k = l;

  while (i < n1 && j < n2) {
    (*comparisons)++; // Comparação de chaves
    if (L[i] <= R[j]) {
      arr[k] = L[i];
      i++;
    } else {
      arr[k] = R[j];
      j++;
    }
    (*movements)++; // Movimentação para array final
    k++;
  }

  while (i < n1) {
    arr[k] = L[i];
    i++;
    k++;
    (*movements)++; // Movimentação de restante do array L
  }

  while (j < n2) {
    arr[k] = R[j];
    j++;
    k++;
    (*movements)++; // Movimentação de restante do array R
  }
}

void mergeSort(int arr[], int l, int r, int *comparisons, int *movements) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, l, m, comparisons, movements);
    mergeSort(arr, m + 1, r, comparisons, movements);
    merge(arr, l, m, r, comparisons, movements);
  }
  /* Complexidade:
- Tempo: O(n log n) em todos os casos
- Espaço: O(n) (não é in-place devido à necessidade de arrays temporários)
*/
}

// Funções para o HeapSort

// Função para a criação da árvore binária e seu rearranjo
void heapify(int arr[], int n, int i, int *comparisons, int *movements) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n) {
    (*comparisons)++;
    if (arr[left] > arr[largest])
      largest = left;
  }

  if (right < n) {
    (*comparisons)++;
    if (arr[right] > arr[largest])
      largest = right;
  }

  if (largest != i) {
    int temp = arr[i];
    arr[i] = arr[largest];
    arr[largest] = temp;
    (*movements) += 3; // Swap
    heapify(arr, n, largest, comparisons, movements);
  }
}

void heapSort(int arr[], int n, int *comparisons, int *movements) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i, comparisons, movements);

  for (int i = n - 1; i > 0; i--) {
    int temp = arr[0];
    arr[0] = arr[i];
    arr[i] = temp;
    (*movements) += 3; // Swap
    heapify(arr, i, 0, comparisons, movements);
  }
  /* Complexidade:
- Tempo: O(n log n) em todos os casos
- Espaço: O(1) (ordenado in-place)
*/
}

// Funções para o RadixSort
int getMax(int arr[], int n, int *comparisons) {
  int max = arr[0];
  for (int i = 1; i < n; i++) {
    (*comparisons)++;
    if (arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}

void countingSortForRadix(int arr[], int n, int exp, int *comparisons,
                          int *movements) {
  int output[n];
  int count[10] = {0};

  for (int i = 0; i < n; i++) {
    count[(arr[i] / exp) % 10]++;
    (*movements)++; // Contagem de movimentação
  }

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = n - 1; i >= 0; i--) {
    output[count[(arr[i] / exp) % 10] - 1] = arr[i];
    count[(arr[i] / exp) % 10]--;
    (*movements)++; // Movimentação para array final
  }

  for (int i = 0; i < n; i++) {
    arr[i] = output[i];
    (*movements)++; // Movimentação de volta para o array original
  }
}

void radixSort(int arr[], int n, int *comparisons, int *movements) {
  int max = getMax(arr, n, comparisons);

  for (int exp = 1; max / exp > 0; exp *= 10)
    countingSortForRadix(arr, n, exp, comparisons, movements);
  /* Complexidade:
- Tempo: O(nk), onde k é o número de dígitos no maior número
- Espaço: O(n) (para o array de saída)
*/
}
