// Memory Benchmark: SIMD Sum (C baseline)
// Goal: Measure auto-vectorization potential
//
// Simple array sum that should be auto-vectorized with -O3

#include <stdio.h>
#include <stdint.h>

#define SIZE 64
#define ITERATIONS 10000

// Sum array elements - SIMD-friendly pattern
int64_t sum_array(int64_t* arr) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        acc += arr[i];
    }
    return acc;
}

// Sum with unrolled access (4 elements at a time)
int64_t sum_unrolled(int64_t* arr) {
    int64_t acc = 0;
    int i;
    for (i = 0; i + 3 < SIZE; i += 4) {
        acc += arr[i] + arr[i + 1] + arr[i + 2] + arr[i + 3];
    }
    for (; i < SIZE; i++) {
        acc += arr[i];
    }
    return acc;
}

// Dot product - classic SIMD operation
int64_t dot_product(int64_t* a, int64_t* b) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        acc += a[i] * b[i];
    }
    return acc;
}

int main() {
    int64_t arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    int64_t total = 0;
    for (int iter = 0; iter < ITERATIONS; iter++) {
        int64_t sum1 = sum_array(arr);
        int64_t sum2 = sum_unrolled(arr);
        int64_t dot = dot_product(arr, arr);
        total += sum1 + sum2 + dot;
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
