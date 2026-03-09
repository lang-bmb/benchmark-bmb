// Array Cumulative Max — running maximum of array
// Measures: sequential scan, register tracking (cur_max), branch prediction
// Workload: N=2000000 array, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t cumulative_max(int64_t* arr, int64_t n) {
    int64_t cur_max = arr[0];
    int64_t total = cur_max;
    for (int64_t i = 1; i < n; i++) {
        if (arr[i] > cur_max) {
            cur_max = arr[i];
        }
        total += cur_max;
    }
    return total;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 1000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000;
        }
        checksum += cumulative_max(arr, N);
    }

    printf("%lld\n", (long long)(checksum % 1000000007));
    free(arr);
    return 0;
}
