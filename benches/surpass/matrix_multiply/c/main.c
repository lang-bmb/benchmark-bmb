// Surpass Benchmark: Matrix Multiply (C baseline)
// Goal: BMB > C through contract-based aliasing guarantees
//
// C uses restrict keyword for aliasing hints, but compiler
// cannot always prove safety like BMB contracts can

#include <stdio.h>
#include <stdint.h>

#define SIZE 8
#define ITERATIONS 1000

// Matrix element access
static inline int64_t mat_get(int64_t* mat, int row, int col) {
    return mat[row * SIZE + col];
}

// Compute single cell (dot product)
static inline int64_t compute_cell(
    int64_t* restrict a,
    int64_t* restrict b,
    int row, int col
) {
    int64_t acc = 0;
    for (int k = 0; k < SIZE; k++) {
        acc += mat_get(a, row, k) * mat_get(b, k, col);
    }
    return acc;
}

// Sum all cells of result matrix
int64_t matrix_multiply_sum(int64_t* restrict a, int64_t* restrict b) {
    int64_t total = 0;
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            total += compute_cell(a, b, row, col);
        }
    }
    return total;
}

int main() {
    int64_t a[SIZE * SIZE] = {
        1, 2, 3, 4, 5, 6, 7, 8,
        2, 3, 4, 5, 6, 7, 8, 9,
        3, 4, 5, 6, 7, 8, 9, 10,
        4, 5, 6, 7, 8, 9, 10, 11,
        5, 6, 7, 8, 9, 10, 11, 12,
        6, 7, 8, 9, 10, 11, 12, 13,
        7, 8, 9, 10, 11, 12, 13, 14,
        8, 9, 10, 11, 12, 13, 14, 15
    };
    int64_t b[SIZE * SIZE] = {
        1, 0, 0, 0, 0, 0, 0, 0,
        0, 1, 0, 0, 0, 0, 0, 0,
        0, 0, 1, 0, 0, 0, 0, 0,
        0, 0, 0, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 0, 0, 0,
        0, 0, 0, 0, 0, 1, 0, 0,
        0, 0, 0, 0, 0, 0, 1, 0,
        0, 0, 0, 0, 0, 0, 0, 1
    };

    int64_t total = 0;
    for (int iter = 0; iter < ITERATIONS; iter++) {
        total += matrix_multiply_sum(a, b);
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
