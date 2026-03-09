// Polynomial Evaluation benchmark — Horner's method
// Measures: array access, multiply-add chains, modular arithmetic
// Workload: degree 1000 polynomial, 5000 points, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t horner_eval(const int64_t* coeffs, int64_t degree, int64_t x, int64_t modulus) {
    int64_t result = coeffs[degree];
    for (int64_t i = degree - 1; i >= 0; i--) {
        result = (result * x + coeffs[i]) % modulus;
    }
    return result;
}

int main() {
    int64_t degree = 1000;
    int64_t n_coeffs = degree + 1;
    int64_t n_points = 5000;
    int64_t iters = 100;
    int64_t modulus = 1000000007;

    int64_t* coeffs = (int64_t*)malloc(n_coeffs * sizeof(int64_t));

    // Generate coefficients using LCG
    int64_t seed = 42;
    for (int64_t i = 0; i < n_coeffs; i++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        coeffs[i] = seed % 1000;
    }

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        for (int64_t x = 1; x <= n_points; x++) {
            checksum += horner_eval(coeffs, degree, x, modulus);
        }
    }

    printf("%lld\n", (long long)(checksum % modulus));
    free(coeffs);
    return 0;
}
