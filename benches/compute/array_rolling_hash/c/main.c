// Rolling Hash — polynomial rolling hash over array
// Measures: register-carry (hash accumulator), sequential scan
// Workload: N=2000000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000, ITERS = 2000;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t checksum = 0, seed = 42;
    int64_t MOD = 1000000007, BASE = 31;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 256;
        }
        int64_t hash = 0;
        int64_t max_hash = 0;
        for (int64_t i = 0; i < N; i++) {
            hash = (hash * BASE + arr[i]) % MOD;
            if (hash > max_hash) max_hash = hash;
        }
        checksum += max_hash;
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    return 0;
}
