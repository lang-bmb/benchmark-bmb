// String Compress — RLE-like compression on integer array
// Measures: sequential scan, conditional counting, output generation
// Workload: N=500000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t compress(const int64_t* src, int64_t n, int64_t* dst) {
    int64_t k = 0;
    int64_t i = 0;
    while (i < n) {
        int64_t val = src[i];
        int64_t count = 1;
        while (i + count < n && src[i + count] == val) {
            count++;
        }
        dst[k++] = val;
        dst[k++] = count;
        i += count;
    }
    return k;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 2000;
    int64_t* src = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* dst = (int64_t*)malloc(2 * N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            src[i] = seed % 10;  // Small alphabet for runs
        }
        int64_t len = compress(src, N, dst);
        checksum += len + dst[0] + dst[len - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(src);
    free(dst);
    return 0;
}
