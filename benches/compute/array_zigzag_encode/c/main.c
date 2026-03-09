// Zigzag Encode — delta + zigzag encode array values
// Measures: register-carry (prev), bitwise operations
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
            arr[i] = seed % 10000 - 5000;
        }
        int64_t prev = 0;
        int64_t total = 0;
        for (int64_t i = 0; i < N; i++) {
            int64_t delta = arr[i] - prev;
            // zigzag encode: (delta << 1) ^ (delta >> 63)
            int64_t encoded = (delta << 1) ^ (delta >> 63);
            total += encoded;
            prev = arr[i];
        }
        checksum += total % 1000000007;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
