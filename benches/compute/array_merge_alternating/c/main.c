// Array Merge Alternating — merge two sorted arrays
// Measures: two-pointer merge, branch prediction, sequential write
// Workload: N=500000 per array, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t merge(const int64_t* a, int64_t na, const int64_t* b, int64_t nb, int64_t* out) {
    int64_t i = 0, j = 0, k = 0;
    while (i < na && j < nb) {
        if (a[i] <= b[j]) {
            out[k++] = a[i++];
        } else {
            out[k++] = b[j++];
        }
    }
    while (i < na) out[k++] = a[i++];
    while (j < nb) out[k++] = b[j++];
    return out[0] + out[k - 1];
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 2000;
    int64_t* a = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* b = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* out = (int64_t*)malloc(2 * N * sizeof(int64_t));

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t prev = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            prev += (seed % 5) + 1;
            a[i] = prev;
        }
        prev = 0;
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            prev += (seed % 5) + 1;
            b[i] = prev;
        }
        checksum += merge(a, N, b, N, out);
    }

    printf("%lld\n", (long long)checksum);
    free(a);
    free(b);
    free(out);
    return 0;
}
