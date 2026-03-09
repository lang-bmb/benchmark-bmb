// Range Update — apply range additions and flatten with prefix sum
// Measures: random access writes, sequential prefix sum scan
// Workload: N=500000 array, 500000 updates, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t NUPS = 500000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) arr[i] = 0;
        for (int64_t i = 0; i < NUPS; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t lo = seed % N;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t hi = lo + (seed % (N - lo));
            arr[lo] += 1;
            if (hi + 1 < N) arr[hi + 1] -= 1;
        }
        for (int64_t i = 1; i < N; i++) {
            arr[i] += arr[i - 1];
        }
        checksum += arr[0] + arr[N / 2] + arr[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
