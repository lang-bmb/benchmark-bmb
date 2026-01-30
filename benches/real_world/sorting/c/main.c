// Sorting benchmark
// Measures: comparison operations, data movement
// v0.60.51: Use int64_t to match BMB's i64 for fair comparison

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void swap(int64_t* a, int64_t* b) {
    int64_t tmp = *a;
    *a = *b;
    *b = tmp;
}

int64_t bubble_sort(int64_t* arr, int64_t n) {
    int64_t comparisons = 0;
    for (int64_t i = 0; i < n - 1; i++) {
        for (int64_t j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
    return comparisons;
}

int64_t insertion_sort(int64_t* arr, int64_t n) {
    int64_t cost = 0;
    for (int64_t i = 1; i < n; i++) {
        int64_t key = arr[i];
        int64_t j = i - 1;
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

void merge(int64_t* arr, int64_t l, int64_t m, int64_t r, int64_t* cost) {
    int64_t n1 = m - l + 1;
    int64_t n2 = r - m;
    int64_t* L = (int64_t*)malloc(n1 * sizeof(int64_t));
    int64_t* R = (int64_t*)malloc(n2 * sizeof(int64_t));

    for (int64_t i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int64_t j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    int64_t i = 0, j = 0, k = l;
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

void merge_sort_helper(int64_t* arr, int64_t l, int64_t r, int64_t* cost) {
    if (l < r) {
        int64_t m = l + (r - l) / 2;
        merge_sort_helper(arr, l, m, cost);
        merge_sort_helper(arr, m + 1, r, cost);
        merge(arr, l, m, r, cost);
    }
}

int64_t merge_sort(int64_t* arr, int64_t n) {
    int64_t cost = 0;
    merge_sort_helper(arr, 0, n - 1, &cost);
    return cost;
}

int64_t partition(int64_t* arr, int64_t low, int64_t high, int64_t* cost) {
    int64_t pivot = arr[high];
    int64_t i = low - 1;
    for (int64_t j = low; j < high; j++) {
        (*cost)++;
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

void quick_sort_helper(int64_t* arr, int64_t low, int64_t high, int64_t* cost) {
    if (low < high) {
        int64_t pi = partition(arr, low, high, cost);
        quick_sort_helper(arr, low, pi - 1, cost);
        quick_sort_helper(arr, pi + 1, high, cost);
    }
}

int64_t quick_sort(int64_t* arr, int64_t n) {
    int64_t cost = 0;
    quick_sort_helper(arr, 0, n - 1, &cost);
    return cost;
}

int main() {
    int64_t total = 0;

    // v0.60: Increased from 50 to 200 for better measurement accuracy
    for (int sizes = 200; sizes > 0; sizes--) {
        int64_t size = sizes * 10;
        int64_t* arr = (int64_t*)malloc(size * sizeof(int64_t));

        // Initialize with reverse order (worst case for some algorithms)
        for (int64_t i = 0; i < size; i++) arr[i] = size - i;
        total += bubble_sort(arr, size);

        for (int64_t i = 0; i < size; i++) arr[i] = size - i;
        total += insertion_sort(arr, size);

        for (int64_t i = 0; i < size; i++) arr[i] = size - i;
        total += merge_sort(arr, size);

        for (int64_t i = 0; i < size; i++) arr[i] = size - i;
        total += quick_sort(arr, size);

        free(arr);
    }

    printf("%lld\n", (long long)total);
    return 0;
}
