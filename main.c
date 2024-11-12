#include "./sorts/sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Função para ler vetor a partir de arquivo .txt
int *lerVetor(const char *nomeArquivo, int *tamanho) {
  FILE *arquivo = fopen(nomeArquivo, "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
    exit(EXIT_FAILURE);
  }

  fscanf(arquivo, "%d", tamanho);
  int *vetor = (int *)malloc((*tamanho) * sizeof(int));
  if (vetor == NULL) {
    printf("Erro ao alocar memória para o vetor.\n");
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < *tamanho; i++) {
    fscanf(arquivo, "%d", &vetor[i]);
  }

  fclose(arquivo);
  return vetor;
}

// Função genérica de medição para algoritmos com assinatura padrão
void medirTempoOrdenacao(void (*sortFunction)(int[], int, int*, int*), int arr[], int n,
                         int *comparisons, int *movements,
                         const char *nomeMetodo) {
  clock_t inicio, fim;
  *comparisons = 0;
  *movements = 0;

  int *arrCopia = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    arrCopia[i] = arr[i];
  }

  inicio = clock();
  sortFunction(arrCopia, n, comparisons, movements);
  fim = clock();
  double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

  printf("Tempo de execução do %s: %f segundos\n", nomeMetodo, tempo);
  printf("Comparações: %d, Movimentos: %d\n", *comparisons, *movements);

  free(arrCopia);
}

// Função para medição de QuickSort
void medirTempoQuickSort(int arr[], int n, int *comparisons, int *movements) {
  clock_t inicio, fim;
  *comparisons = 0;
  *movements = 0;

  int *arrCopia = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    arrCopia[i] = arr[i];
  }

  inicio = clock();
  quicksort(arrCopia, 0, n - 1, comparisons, movements);
  fim = clock();
  double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

  printf("Tempo de execução do QuickSort: %f segundos\n", tempo);
  printf("Comparações: %d, Movimentos: %d\n", *comparisons, *movements);

  free(arrCopia);
}

// Função para medição de MergeSort
void medirTempoMergeSort(int arr[], int n, int *comparisons, int *movements) {
  clock_t inicio, fim;
  *comparisons = 0;
  *movements = 0;

  int *arrCopia = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    arrCopia[i] = arr[i];
  }

  inicio = clock();
  mergeSort(arrCopia, 0, n - 1, comparisons, movements);
  fim = clock();
  double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

  printf("Tempo de execução do MergeSort: %f segundos\n", tempo);
  printf("Comparações: %d, Movimentos: %d\n", *comparisons, *movements);

  free(arrCopia);
}

int main() {
  int comparisons, movements;

  const char *diretorios[] = {"tests/ordered/", "tests/random/", "tests/reversed/"};
  const char *arquivos[] = {"vector_100.txt", "vector_1000.txt", "vector_10000.txt", "vector_100000.txt"};

  for (int d = 0; d < 3; d++) {
    for (int a = 0; a < 4; a++) {
      char caminho[256];
      sprintf(caminho, "%s%s", diretorios[d], arquivos[a]);

      int tamanho;
      int *arr = lerVetor(caminho, &tamanho);

      printf("\nTestando arquivo: %s\n", caminho);

      medirTempoOrdenacao(bubblesort_aprimorado, arr, tamanho, &comparisons, &movements, "BubbleSort Aprimorado");
      medirTempoOrdenacao(selectionSort, arr, tamanho, &comparisons, &movements, "Selection Sort");
      medirTempoOrdenacao(insertionSort, arr, tamanho, &comparisons, &movements, "Insertion Sort");
      medirTempoOrdenacao(shellSort, arr, tamanho, &comparisons, &movements, "Shell Sort");
      medirTempoOrdenacao(countingSmaller, arr, tamanho, &comparisons, &movements, "Counting Smaller");
      medirTempoOrdenacao(heapSort, arr, tamanho, &comparisons, &movements, "Heap Sort");
      medirTempoOrdenacao(radixSort, arr, tamanho, &comparisons, &movements, "Radix Sort");
      medirTempoQuickSort(arr, tamanho, &comparisons, &movements);
      medirTempoMergeSort(arr, tamanho, &comparisons, &movements);

      free(arr);
    }
  }

  return 0;
}
