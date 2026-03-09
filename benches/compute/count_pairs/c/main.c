// Count Pairs — count pairs with difference equal to target
// Measures: sorting + two-pointer search
// Workload: N=200000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void insertion_sort_range(int64_t* arr, int64_t lo, int64_t hi) {
    for (int64_t i = lo + 1; i <= hi; i++) {
        int64_t key = arr[i];
        int64_t j = i - 1;
        while (j >= lo && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

static void quicksort(int64_t* arr, int64_t lo, int64_t hi) {
    while (lo < hi) {
        if (hi - lo < 16) {
            insertion_sort_range(arr, lo, hi);
            return;
        }
        // Median-of-three pivot
        int64_t mid = lo + (hi - lo) / 2;
        if (arr[mid] < arr[lo]) { int64_t t = arr[lo]; arr[lo] = arr[mid]; arr[mid] = t; }
        if (arr[hi] < arr[lo]) { int64_t t = arr[lo]; arr[lo] = arr[hi]; arr[hi] = t; }
        if (arr[mid] < arr[hi]) { int64_t t = arr[mid]; arr[mid] = arr[hi]; arr[hi] = t; }
        int64_t pivot = arr[hi];

        int64_t i = lo - 1;
        for (int64_t j = lo; j < hi; j++) {
            if (arr[j] <= pivot) {
                i++;
                int64_t t = arr[i]; arr[i] = arr[j]; arr[j] = t;
            }
        }
        i++;
        int64_t t = arr[i]; arr[i] = arr[hi]; arr[hi] = t;

        if (i - lo < hi - i) {
            quicksort(arr, lo, i - 1);
            lo = i + 1;
        } else {
            quicksort(arr, i + 1, hi);
            hi = i - 1;
        }
    }
}

int main() {
    int64_t N = 200000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000;
        }
        int64_t target = 42 + iter % 100;

        quicksort(arr, 0, N - 1);

        // Two-pointer count pairs with difference == target
        int64_t count = 0;
        int64_t left = 0, right = 1;
        while (right < N) {
            int64_t diff = arr[right] - arr[left];
            if (diff == target) {
                count++;
                right++;
            } else if (diff < target) {
                right++;
            } else {
                left++;
                if (left == right) right++;
            }
        }
        checksum += count;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
