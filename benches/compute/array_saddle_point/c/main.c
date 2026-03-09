// Array Saddle Point — find matrix elements that are min in row and max in column
// Measures: row/column scans, 2D array access
// Workload: N=500, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 500;
    int64_t ITERS = 3000;
    int64_t* mat = (int64_t*)malloc(N * N * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N * N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            mat[i] = seed % 10000;
        }

        int64_t saddle_count = 0;
        for (int64_t i = 0; i < N; i++) {
            // Find min in row i
            int64_t row_min = mat[i * N];
            int64_t min_col = 0;
            for (int64_t j = 1; j < N; j++) {
                if (mat[i * N + j] < row_min) {
                    row_min = mat[i * N + j];
                    min_col = j;
                }
            }
            // Check if it's max in its column
            int64_t is_max = 1;
            for (int64_t k = 0; k < N; k++) {
                if (mat[k * N + min_col] > row_min) {
                    is_max = 0;
                    break;
                }
            }
            saddle_count += is_max;
        }
        checksum += saddle_count;
    }
    printf("%lld\n", (long long)checksum);
    free(mat);
    return 0;
}
