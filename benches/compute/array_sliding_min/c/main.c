// Sliding Minimum — track running min across sliding window
// Measures: register-carry (running min), sequential scan
// Workload: N=2000000, 500 iterations, window=8

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t K = 8;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 100000;
        }

        // Simple sliding window min with register tracking
        int64_t sum_mins = 0;
        for (int64_t i = 0; i <= N - K; i++) {
            int64_t mn = arr[i];
            for (int64_t j = 1; j < K; j++) {
                int64_t v = arr[i + j];
                if (v < mn) mn = v;
            }
            sum_mins += mn;
        }
        checksum += sum_mins % 1000000007;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
