// Sorting benchmark
// Measures: comparison operations, data movement

#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

long bubble_sort(int* arr, int n) {
    long comparisons = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    return comparisons;
}

long insertion_sort(int* arr, int n) {
    long cost = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            cost++;
        }
        arr[j + 1] = key;
        cost++;
    }
    return cost;
}

void merge(int* arr, int l, int m, int r, long* cost) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        (*cost)++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    free(L);
    free(R);
}

void merge_sort_helper(int* arr, int l, int r, long* cost) {
    if (l < r) {
        int m = l + (r - l) / 2;
        merge_sort_helper(arr, l, m, cost);
        merge_sort_helper(arr, m + 1, r, cost);
        merge(arr, l, m, r, cost);
    }
}

long merge_sort(int* arr, int n) {
    long cost = 0;
    merge_sort_helper(arr, 0, n - 1, &cost);
    return cost;
}

int partition(int* arr, int low, int high, long* cost) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        (*cost)++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort_helper(int* arr, int low, int high, long* cost) {
    if (low < high) {
        int pi = partition(arr, low, high, cost);
        quick_sort_helper(arr, low, pi - 1, cost);
        quick_sort_helper(arr, pi + 1, high, cost);
    }
}

long quick_sort(int* arr, int n) {
    long cost = 0;
    quick_sort_helper(arr, 0, n - 1, &cost);
    return cost;
}

int main() {
    long total = 0;

    for (int sizes = 50; sizes > 0; sizes--) {
        int size = sizes * 10;
        int* arr = (int*)malloc(size * sizeof(int));

        // Initialize with reverse order (worst case for some algorithms)
        for (int i = 0; i < size; i++) arr[i] = size - i;
        total += bubble_sort(arr, size);

        for (int i = 0; i < size; i++) arr[i] = size - i;
        total += insertion_sort(arr, size);

        for (int i = 0; i < size; i++) arr[i] = size - i;
        total += merge_sort(arr, size);

        for (int i = 0; i < size; i++) arr[i] = size - i;
        total += quick_sort(arr, size);

        free(arr);
    }

    printf("%ld\n", total);
    return 0;
}
