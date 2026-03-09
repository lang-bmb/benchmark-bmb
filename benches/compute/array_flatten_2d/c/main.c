// Array Flatten 2D — copy 2D row-major data into 1D array
// Measures: nested loop, sequential write, stride read
// Workload: 1000x1000 matrix, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t ROWS = 1000;
    int64_t COLS = 1000;
    int64_t N = ROWS * COLS;
    int64_t ITERS = 3000;
    int64_t* mat = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* flat = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        mat[i] = seed;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t idx = 0;
        for (int64_t r = 0; r < ROWS; r++) {
            for (int64_t c = 0; c < COLS; c++) {
                flat[idx++] = mat[r * COLS + c];
            }
        }
        checksum += flat[0] + flat[N - 1];
    }

    printf("%lld\n", (long long)checksum);
    free(mat);
    free(flat);
    return 0;
}
