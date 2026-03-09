// Array Partition — Lomuto partition scheme (quicksort partition step)
// Measures: sequential scan, conditional swap, branch prediction
// Workload: N=100000 array, 10000 partitions

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t partition(int64_t* arr, int64_t lo, int64_t hi) {
    int64_t pivot = arr[hi];
    int64_t i = lo - 1;
    for (int64_t j = lo; j < hi; j++) {
        if (arr[j] <= pivot) {
            i++;
            int64_t tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
        }
    }
    int64_t tmp = arr[i + 1];
    arr[i + 1] = arr[hi];
    arr[hi] = tmp;
    return i + 1;
}

int main() {
    int64_t N = 100000;
    int64_t ITERS = 10000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Fill with pseudo-random values
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % N;
        }
        int64_t pivot_idx = partition(arr, 0, N - 1);
        checksum += pivot_idx + arr[0] + arr[N / 2];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
