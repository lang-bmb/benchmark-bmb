// Heapsort benchmark — in-place heap sort
// Measures: heap operations, array swaps, cache-unfriendly access
// Workload: 500K elements, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define N 500000
#define ITERS 100

static void sift_down(int64_t* arr, int64_t n, int64_t i) {
    while (1) {
        int64_t largest = i;
        int64_t l = 2 * i + 1;
        int64_t r = 2 * i + 2;
        if (l < n && arr[l] > arr[largest]) largest = l;
        if (r < n && arr[r] > arr[largest]) largest = r;
        if (largest == i) break;
        int64_t tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        i = largest;
    }
}

static void heapsort(int64_t* arr, int64_t n) {
    // Build max-heap
    for (int64_t i = n / 2 - 1; i >= 0; i--) {
        sift_down(arr, n, i);
    }
    // Extract elements
    for (int64_t i = n - 1; i > 0; i--) {
        int64_t tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;
        sift_down(arr, i, 0);
    }
}

int main() {
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 27182 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed;
        }
        heapsort(arr, N);
        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
