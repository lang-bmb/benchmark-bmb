// String Reverse benchmark — reverse a 100000-character i64 array
// Measures: array read/write, swap pattern, memory access
// Workload: 100000 chars, 5000 iterations, LCG PRNG

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t fill_string(int64_t* arr, int64_t n, int64_t seed_in) {
    int64_t seed = seed_in;
    for (int64_t i = 0; i < n; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = (seed % 26) + 97;
    }
    return seed;
}

static void reverse_string(int64_t* arr, int64_t n) {
    int64_t lo = 0;
    int64_t hi = n - 1;
    while (lo < hi) {
        int64_t tmp = arr[lo];
        arr[lo] = arr[hi];
        arr[hi] = tmp;
        lo++;
        hi--;
    }
}

static int64_t checksum(int64_t* arr, int64_t n) {
    int64_t sum_val = 0;
    for (int64_t i = 0; i < 10; i++) {
        sum_val += arr[i];
    }
    for (int64_t j = 0; j < 10; j++) {
        sum_val += arr[n - 10 + j];
    }
    return sum_val;
}

int main() {
    int64_t n = 100000;
    int64_t iters = 5000;
    int64_t* arr = (int64_t*)malloc(n * sizeof(int64_t));

    int64_t total = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        fill_string(arr, n, 12345 + iter);
        reverse_string(arr, n);
        total += checksum(arr, n);
    }

    printf("%lld\n", (long long)total);
    free(arr);
    return 0;
}
