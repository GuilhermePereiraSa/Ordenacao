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

  // Primeiro número no arquivo é o tamanho do vetor
  fscanf(arquivo, "%d", tamanho);

  // Alocar espaço para o vetor
  int *vetor = (int *)malloc((*tamanho) * sizeof(int));
  if (vetor == NULL) {
    printf("Erro ao alocar memória para o vetor.\n");
    exit(EXIT_FAILURE);
  }

  // Ler os elementos do vetor
  for (int i = 0; i < *tamanho; i++) {
    fscanf(arquivo, "%d", &vetor[i]);
  }

  fclose(arquivo);
  return vetor;
}

// Função para medir tempo de execução e registrar comparações e movimentos
void medirTempoOrdenacao(void (*sortFunction)(), int arr[], int n,
                         int *comparisons, int *movements,
                         const char *nomeMetodo) {
  clock_t inicio, fim;
  *comparisons = 0;
  *movements = 0;

  // Copia o vetor original para preservá-lo
  int *arrCopia = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    arrCopia[i] = arr[i];
  }

  inicio = clock();

  // Chama a função de ordenação
  sortFunction(arrCopia, n, comparisons, movements);

  fim = clock();
  double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

  printf("Tempo de execução do %s: %f segundos\n", nomeMetodo, tempo);
  printf("Comparações: %d, Movimentos: %d\n", *comparisons, *movements);

  free(arrCopia);
}

// Função específica para QuickSort
void medirTempoQuickSort(int arr[], int n, int *comparisons, int *movements) {
  clock_t inicio, fim;
  *comparisons = 0;
  *movements = 0;

  // Copia o vetor original para preservá-lo
  int *arrCopia = (int *)malloc(n * sizeof(int));
  for (int i = 0; i < n; i++) {
    arrCopia[i] = arr[i];
  }

  inicio = clock();

  // Chama o quicksort
  quicksort(arrCopia, 0, n - 1, comparisons, movements);

  fim = clock();
  double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

  printf("Tempo de execução do QuickSort: %f segundos\n", tempo);
  printf("Comparações: %d, Movimentos: %d\n", *comparisons, *movements);

  free(arrCopia);
}

int main() {
  int comparisons, movements;

  // Diretórios e tamanhos de vetores
  const char *diretorios[] = {"tests/ordered/", "tests/random/",
                              "tests/reversed/"};
  const char *arquivos[] = {"vector_100.txt", "vector_1000.txt",
                            "vector_10000.txt", "vector_100000.txt"};

  // Percorre todos os diretórios e arquivos
  for (int d = 0; d < 3; d++) {
    for (int a = 0; a < 4; a++) {
      char caminho[256];
      sprintf(caminho, "%s%s", diretorios[d], arquivos[a]);

      // Lê o vetor do arquivo correspondente
      int tamanho;
      int *arr = lerVetor(caminho, &tamanho);

      printf("\nTestando arquivo: %s\n", caminho);

      // Medir tempo para cada método de ordenação
      medirTempoOrdenacao((void *)bubblesort_aprimorado, arr, tamanho,
                          &comparisons, &movements, "BubbleSort Aprimorado");
      medirTempoOrdenacao((void *)selectionSort, arr, tamanho, &comparisons,
                          &movements, "Selection Sort");
      medirTempoOrdenacao((void *)insertionSort, arr, tamanho, &comparisons,
                          &movements, "Insertion Sort");
      medirTempoOrdenacao((void *)shellSort, arr, tamanho, &comparisons,
                          &movements, "Shell Sort");
      medirTempoOrdenacao((void *)countingSmaller, arr, tamanho, &comparisons,
                          &movements, "Counting Smaller");
      medirTempoOrdenacao((void *)mergeSort, arr, tamanho, &comparisons,
                          &movements, "Merge Sort");
      medirTempoOrdenacao((void *)heapSort, arr, tamanho, &comparisons,
                          &movements, "Heap Sort");
      medirTempoOrdenacao((void *)radixSort, arr, tamanho, &comparisons,
                          &movements, "Radix Sort");
      medirTempoQuickSort(arr, tamanho, &comparisons, &movements);

      free(arr); // Libera memória alocada para o vetor
    }
  }

  return 0;
}
