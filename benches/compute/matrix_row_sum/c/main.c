// Matrix Row Sum — compute sum of each row
// Measures: row-major access, accumulator pattern, sequential read
// Workload: 1000x1000 matrix, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 1000;
    int64_t SZ = N * N;
    int64_t ITERS = 5000;
    int64_t* mat = (int64_t*)malloc(SZ * sizeof(int64_t));
    int64_t* sums = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < SZ; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        mat[i] = seed % 1000;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t r = 0; r < N; r++) {
            int64_t s = 0;
            for (int64_t c = 0; c < N; c++) {
                s += mat[r * N + c];
            }
            sums[r] = s;
        }
        checksum += sums[0] + sums[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(mat);
    free(sums);
    return 0;
}
