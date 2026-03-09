// EWMA — exponential weighted moving average (integer approx)
// Measures: register-carry (accumulator), sequential scan
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
            arr[i] = seed % 10000;
        }
        // EWMA with alpha=1/8 (shift by 3): ewma = ewma*7/8 + val/8
        int64_t ewma = arr[0] * 1024; // scale by 1024
        int64_t max_ewma = ewma;
        for (int64_t i = 1; i < N; i++) {
            ewma = ewma - (ewma >> 3) + (arr[i] * 1024 >> 3);
            if (ewma > max_ewma) max_ewma = ewma;
        }
        checksum += max_ewma >> 10;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
