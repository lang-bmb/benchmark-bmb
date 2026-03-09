// Matrix Power — repeated squaring (binary exponentiation)
// Measures: matrix multiply, modular arithmetic, bit operations, memory access
// Workload: 4x4 matrices, exponent ~10^9, 500000 iterations with different matrices

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static void mat_mul(int64_t* a, int64_t* b, int64_t* c, int64_t n, int64_t modv) {
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < n; j++) {
            int64_t sum = 0;
            for (int64_t k = 0; k < n; k++) {
                sum = (sum + a[i * n + k] * b[k * n + j]) % modv;
            }
            c[i * n + j] = sum;
        }
    }
}

static void mat_copy(int64_t* src, int64_t* dst, int64_t n) {
    for (int64_t i = 0; i < n * n; i++) {
        dst[i] = src[i];
    }
}

static void mat_identity(int64_t* m, int64_t n) {
    for (int64_t i = 0; i < n; i++) {
        for (int64_t j = 0; j < n; j++) {
            m[i * n + j] = (i == j) ? 1 : 0;
        }
    }
}

static int64_t* mat_pow(int64_t* base, int64_t exp, int64_t n, int64_t modv) {
    int64_t* result = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t* tmp = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t* bcopy = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t* btmp = (int64_t*)malloc(n * n * sizeof(int64_t));

    mat_identity(result, n);
    mat_copy(base, bcopy, n);

    int64_t e = exp;
    while (e > 0) {
        if (e & 1) {
            mat_mul(result, bcopy, tmp, n, modv);
            mat_copy(tmp, result, n);
        }
        mat_mul(bcopy, bcopy, btmp, n, modv);
        mat_copy(btmp, bcopy, n);
        e >>= 1;
    }

    free(tmp);
    free(bcopy);
    free(btmp);
    return result;
}

static int64_t mat_checksum(int64_t* m, int64_t n, int64_t modv) {
    int64_t sum = 0;
    for (int64_t i = 0; i < n * n; i++) {
        sum = (sum + m[i]) % modv;
    }
    return sum;
}

int main() {
    int64_t n = 4;
    int64_t modv = 1000000007;
    int64_t iters = 500000;
    int64_t exp_base = 1000000000;

    int64_t* mat = (int64_t*)malloc(n * n * sizeof(int64_t));
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < iters; iter++) {
        // Fill matrix with PRNG values
        for (int64_t idx = 0; idx < n * n; idx++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            mat[idx] = seed % 100;
        }

        // Vary exponent slightly per iteration
        int64_t exp = exp_base + iter * 7;
        int64_t* result = mat_pow(mat, exp, n, modv);
        checksum = (checksum + mat_checksum(result, n, modv)) % modv;
        free(result);
    }

    free(mat);
    printf("%lld\n", (long long)checksum);
    return 0;
}