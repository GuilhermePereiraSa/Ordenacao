#ifndef SORT_H
    #define SORT_H

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

#endif