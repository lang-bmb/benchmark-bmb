// Running Median — compute median of sliding window using insertion sort
// Measures: small-array insert/shift, conditional branches
// Workload: N=100000 array, window=31, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void insert_sorted(int64_t* win, int64_t size, int64_t val) {
    int64_t i = size - 1;
    while (i >= 0 && win[i] > val) {
        win[i + 1] = win[i];
        i--;
    }
    win[i + 1] = val;
}

int main() {
    int64_t N = 100000;
    int64_t W = 31;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* win = (int64_t*)malloc(W * sizeof(int64_t));

    int64_t seed = 42;
    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10000;
        }
        for (int64_t i = 0; i <= N - W; i++) {
            win[0] = arr[i];
            for (int64_t j = 1; j < W; j++) {
                insert_sorted(win, j, arr[i + j]);
            }
            checksum += win[W / 2];
        }
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    free(win);
    return 0;
}
