#ifndef SORT_H
    #define SORT_H

    
    void selectionSort(int arr[], int n, int *comparisons, int *movements);
    void insertionSort(int arr[], int n, int *comparisons, int *movements);
    void shellSort(int arr[], int n, int *comparisons, int *movements);

    void bubblesort_aprimorado(int v[], int n, int *comparisons, int *movements);
    void countingSmaller(int arr[], int n, int *comparisons, int *movements);


    void mergeSort(int arr[], int l, int r, int *comparisons, int *movements);
    void quicksort(int arr[], int low, int high, int *comparisons, int *movements);
    void heapSort(int arr[], int n, int *comparisons, int *movements);

    void radixSort(int arr[], int n, int *comparisons, int *movements);

#endif