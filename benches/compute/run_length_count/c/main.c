// Run-Length Count — count consecutive runs in array
// Measures: sequential scan, branch prediction, simple counting
// Workload: N=100000 array, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t count_runs(const int64_t* arr, int64_t n) {
    if (n == 0) return 0;
    int64_t runs = 1;
    for (int64_t i = 1; i < n; i++) {
        if (arr[i] != arr[i - 1]) runs++;
    }
    return runs;
}

int main() {
    int64_t N = 100000;
    int64_t ITERS = 10000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Fill array with values 0-9 (creates many runs)
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 10;
        }
        checksum += count_runs(arr, N);
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
