// Spiral Matrix — traverse matrix in spiral order, compute sum
// Measures: direction changes, boundary tracking, sequential access
// Workload: 500x500 matrix, 5000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t spiral_sum(const int64_t* mat, int64_t rows, int64_t cols) {
    int64_t sum = 0;
    int64_t top = 0, bottom = rows - 1, left = 0, right = cols - 1;

    while (top <= bottom && left <= right) {
        for (int64_t j = left; j <= right; j++)
            sum += mat[top * cols + j];
        top++;

        for (int64_t i = top; i <= bottom; i++)
            sum += mat[i * cols + right];
        right--;

        if (top <= bottom) {
            for (int64_t j = right; j >= left; j--)
                sum += mat[bottom * cols + j];
            bottom--;
        }

        if (left <= right) {
            for (int64_t i = bottom; i >= top; i--)
                sum += mat[i * cols + left];
            left++;
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
        checksum += spiral_sum(mat, ROWS, COLS);
        mat[0] = (mat[0] + iter) % 100;
    }

    printf("%lld\n", (long long)checksum);
    free(mat);
    return 0;
}
