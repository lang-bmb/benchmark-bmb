// Merge Sorted Arrays — merge two pre-sorted arrays into one
// Measures: two-pointer merge, sequential access
// Workload: N=500000 each, 1000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500000;
    int64_t ITERS = 1000;
    int64_t* a = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* b = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* out = (int64_t*)malloc(2 * N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        // Generate sorted arrays via cumulative random increments
        int64_t val = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            val += seed % 5 + 1;
            a[i] = val;
        }
        val = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            val += seed % 5 + 1;
            b[i] = val;
        }

        // Merge
        int64_t i = 0, j = 0, k = 0;
        while (i < N && j < N) {
            if (a[i] <= b[j]) {
                out[k++] = a[i++];
            } else {
                out[k++] = b[j++];
            }
        }
        while (i < N) out[k++] = a[i++];
        while (j < N) out[k++] = b[j++];

        checksum += out[0] + out[N] + out[2 * N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(a);
    free(b);
    free(out);
    return 0;
}
