// Polynomial Multiply — convolution of two polynomials
// Measures: nested loops, multiply-accumulate, memory access
// Workload: degree 1000 polynomials, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void poly_mul(const int64_t* a, int64_t na, const int64_t* b, int64_t nb, int64_t* c) {
    int64_t nc = na + nb - 1;
    for (int64_t i = 0; i < nc; i++) c[i] = 0;
    for (int64_t i = 0; i < na; i++) {
        int64_t ai = a[i];
        for (int64_t j = 0; j < nb; j++) {
            c[i + j] += ai * b[j];
        }
    }
}

int main() {
    int64_t N = 1000;
    int64_t ITERS = 500;
    int64_t* a = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* b = (int64_t*)malloc(N * sizeof(int64_t));
    int64_t* c = (int64_t*)malloc(2 * N * sizeof(int64_t));

    int64_t seed = 42;
    for (int64_t i = 0; i < N; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        a[i] = seed % 100;
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        b[i] = seed % 100;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        poly_mul(a, N, b, N, c);
        checksum += c[0] + c[N - 1] + c[2 * N - 2];
    }

    printf("%lld\n", (long long)checksum);
    free(a);
    free(b);
    free(c);
    return 0;
}
