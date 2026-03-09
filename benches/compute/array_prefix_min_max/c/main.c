// Prefix Min Max — compute prefix min and prefix max simultaneously
// Measures: register-carry (running min/max), dual accumulator
// Workload: N=2000000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000;
        }
        int64_t pmin = arr[0], pmax = arr[0];
        int64_t sum_range = 0;
        for (int64_t i = 1; i < N; i++) {
            if (arr[i] < pmin) pmin = arr[i];
            if (arr[i] > pmax) pmax = arr[i];
            sum_range += pmax - pmin;
        }
        checksum += sum_range % 1000000007;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
