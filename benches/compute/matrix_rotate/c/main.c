// Matrix Rotate — 90-degree clockwise rotation of NxN matrix
// Measures: non-sequential access, cache behavior
// Workload: N=1000, 2000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000;
    int64_t ITERS = 2000;
    int64_t* src = (int64_t*)malloc(N * N * sizeof(int64_t));
    int64_t* dst = (int64_t*)malloc(N * N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N * N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            src[i] = seed % 1000;
        }

        // Rotate 90 degrees clockwise: dst[j][N-1-i] = src[i][j]
        for (int64_t i = 0; i < N; i++) {
            for (int64_t j = 0; j < N; j++) {
                dst[j * N + (N - 1 - i)] = src[i * N + j];
            }
        }

        checksum += dst[0] + dst[N * N / 2] + dst[N * N - 1];
    }
    printf("%lld\n", (long long)checksum);
    free(src);
    free(dst);
    return 0;
}
