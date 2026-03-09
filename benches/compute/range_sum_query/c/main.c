// Range Sum Query — prefix sum array for O(1) range queries
// Measures: prefix computation, random access queries
// Workload: N=1000000, 10000 queries, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000000;
    int64_t Q = 10000;
    int64_t ITERS = 500;
    int64_t* arr = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* prefix = (int64_t*)malloc((N + 1) * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            arr[i] = seed % 1000;
        }

        // Build prefix sum
        prefix[0] = 0;
        for (int64_t i = 0; i < N; i++) {
            prefix[i + 1] = prefix[i] + arr[i];
        }

        // Answer Q random range queries
        for (int64_t q = 0; q < Q; q++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t l = seed % N;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t r = seed % N;
            if (l > r) { int64_t t = l; l = r; r = t; }
            checksum += prefix[r + 1] - prefix[l];
        }
    }
    printf("%lld\n", (long long)checksum);
    free(arr);
    free(prefix);
    return 0;
}
