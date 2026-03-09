// Zigzag Matrix Traversal — traverse matrix in zigzag order
// Measures: irregular access pattern, branch prediction, direction changes
// Workload: 500x500 matrix, 3000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t zigzag_sum(const int64_t* mat, int64_t rows, int64_t cols) {
    int64_t sum = 0;
    for (int64_t d = 0; d < rows + cols - 1; d++) {
        int64_t r_start = (d < cols) ? 0 : d - cols + 1;
        int64_t r_end = (d < rows) ? d : rows - 1;
        if (d % 2 == 0) {
            // Up-right: from (r_end, d-r_end) to (r_start, d-r_start)
            for (int64_t r = r_end; r >= r_start; r--) {
                sum += mat[r * cols + (d - r)];
            }
        } else {
            // Down-left: from (r_start, d-r_start) to (r_end, d-r_end)
            for (int64_t r = r_start; r <= r_end; r++) {
                sum += mat[r * cols + (d - r)];
            }
        }
    }
    return sum;
}

int main() {
    int64_t ROWS = 500;
    int64_t COLS = 500;
    int64_t ITERS = 10000;
    int64_t* mat = (int64_t*)malloc(ROWS * COLS * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < ROWS * COLS; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        mat[i] = seed % 100;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        checksum += zigzag_sum(mat, ROWS, COLS);
        // Perturb first element
        mat[0] = (mat[0] + iter) % 100;
    }

    printf("%lld\n", (long long)checksum);
    free(mat);
    return 0;
}
