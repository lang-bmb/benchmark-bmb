// Matrix Multiplication Benchmark
// Measures: nested loops, memory access patterns, cache behavior

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void matrix_init(int64_t* m, int64_t n, int64_t seed) {
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < n; j++) {
            m[i * n + j] = (i * n + j + seed) % 100;
        }
    }
}

void matrix_multiply(int64_t* a, int64_t* b, int64_t* c, int64_t n) {
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < n; j++) {
            int64_t sum = 0;
            for (int64_t k = 0; k < n; k++) {
                sum += a[i * n + k] * b[k * n + j];
            }
            c[i * n + j] = sum;
        }
    }
}

int64_t matrix_sum(int64_t* m, int64_t n) {
    int64_t sum = 0;
    for (int64_t i = 0; i < n * n; i++) {
        sum += m[i];
    }
    return sum;
}

int main() {
    int64_t n = 128;
    int64_t result = 0;

    for (int iter = 0; iter < 10; iter++) {
        int64_t* a = (int64_t*)malloc(n * n * sizeof(int64_t));
        int64_t* b = (int64_t*)malloc(n * n * sizeof(int64_t));
        int64_t* c = (int64_t*)malloc(n * n * sizeof(int64_t));

        matrix_init(a, n, 1);
        matrix_init(b, n, 2);
        matrix_multiply(a, b, c, n);
        result += matrix_sum(c, n);

        free(a);
        free(b);
        free(c);
    }

    printf("%lld\n", (long long)result);
    return 0;
}
