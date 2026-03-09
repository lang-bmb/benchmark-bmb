// Prefix Sum — linear scan accumulation
// Measures: sequential memory access, running sum, cache locality
// Workload: N=10M array, 20 iterations, compute prefix sums then range queries

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void prefix_sum(int64_t* arr, int64_t* prefix, int64_t n) {
    prefix[0] = arr[0];
    for (int64_t i = 1; i < n; i++) {
        prefix[i] = prefix[i - 1] + arr[i];
    }
}

static int64_t range_sum(int64_t* prefix, int64_t l, int64_t r) {
    if (l == 0) return prefix[r];
    return prefix[r] - prefix[l - 1];
}

int main() {
    int64_t N = 10000000;
    int64_t ITERS = 20;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* prefix = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t seed = 999 + iter;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000;
        }
        prefix_sum(arr, prefix, N);
        for (int64_t q = 0; q < 1000; q++) {
            int64_t l = (q * 7919) % N;
            int64_t r_raw = l + (q * 13 + 1) % 10000;
            int64_t r = r_raw >= N ? N - 1 : r_raw;
            checksum += range_sum(prefix, l, r);
        }
    }

    printf("%lld\n", (long long)(checksum % 1000000007));
    free(arr);
    free(prefix);
    return 0;
}