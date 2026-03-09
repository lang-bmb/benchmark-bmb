// Array Rotate — rotate array elements left by k positions
// Measures: reverse pattern, sequential access, in-place mutation
// Workload: N=500000, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void reverse(int64_t* arr, int64_t lo, int64_t hi) {
    while (lo < hi) {
        int64_t tmp = arr[lo];
        arr[lo] = arr[hi];
        arr[hi] = tmp;
        lo++;
        hi--;
    }
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 3000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        arr[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t k = (iter * 7 + 13) % N;
        reverse(arr, 0, k - 1);
        reverse(arr, k, N - 1);
        reverse(arr, 0, N - 1);
        checksum += arr[0] + arr[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
