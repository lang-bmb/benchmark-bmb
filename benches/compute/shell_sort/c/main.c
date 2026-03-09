// Shell Sort benchmark — diminishing increment sort
// Measures: strided array access, gap sequence optimization
// Workload: N=10000 array, 200 iterations, Knuth gap sequence

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void shell_sort(int64_t* arr, int64_t n) {
    // Compute largest gap in Knuth sequence: 1, 4, 13, 40, 121, ...
    int64_t gap = 1;
    while (gap * 3 + 1 < n) {
        gap = gap * 3 + 1;
    }
    while (gap > 0) {
        for (int64_t i = gap; i < n; i++) {
            int64_t key = arr[i];
            int64_t j = i - gap;
            while (j >= 0 && arr[j] > key) {
                arr[j + gap] = arr[j];
                j -= gap;
            }
            arr[j + gap] = key;
        }
        gap = (gap - 1) / 3;
    }
}

int main() {
    int64_t N = 10000;
    int64_t ITERS = 200;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 12345 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % N;
        }
        shell_sort(arr, N);
        for (int64_t i = 0; i < 10; i++) {
            checksum += arr[i];
        }
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}