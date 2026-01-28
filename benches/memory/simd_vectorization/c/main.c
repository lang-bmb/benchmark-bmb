// SIMD Vectorization - Vector operations benchmark
// Measures: Memory bandwidth, auto-vectorization, SIMD potential
//
// This benchmark tests patterns that compilers can auto-vectorize
// Compile with: gcc -O3 -march=native -ftree-vectorize

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define ARRAY_SIZE 1000000

// Pattern 1: Vector addition (a + b -> c)
void vector_add(const int64_t *a, const int64_t *b, int64_t *c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }
}

// Pattern 2: Scalar multiplication (a * scalar -> c)
void vector_scale(const int64_t *a, int64_t scalar, int64_t *c, int n) {
    for (int i = 0; i < n; i++) {
        c[i] = a[i] * scalar;
    }
}

// Pattern 3: Dot product (sum of a[i] * b[i])
int64_t dot_product(const int64_t *a, const int64_t *b, int n) {
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] * b[i];
    }
    return sum;
}

// Pattern 4: Reduction (sum all elements)
int64_t vector_sum(const int64_t *a, int n) {
    int64_t sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

// Pattern 5: Saxpy (scalar * x + y -> result)
void saxpy(const int64_t *x, const int64_t *y, int64_t *result, int n, int64_t scalar) {
    for (int i = 0; i < n; i++) {
        result[i] = scalar * x[i] + y[i];
    }
}

// Pattern 6: Max element (horizontal max)
int64_t vector_max(const int64_t *a, int n) {
    if (n == 0) return 0;
    int64_t max_val = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max_val) {
            max_val = a[i];
        }
    }
    return max_val;
}

// Pattern 7: Copy with stride (gather/scatter pattern)
void strided_copy(const int64_t *src, int64_t *dst, int n, int stride) {
    for (int i = 0, j = 0; i < n; i++, j++) {
        dst[j] = src[i * stride];
    }
}

// Pattern 8: Polynomial computation (Horner's method)
void poly_compute(const int64_t *coeffs, const int64_t *x, int ncoeffs, int64_t *result, int len) {
    for (int k = 0; k < len; k++) {
        int64_t val = coeffs[ncoeffs - 1];
        for (int i = ncoeffs - 2; i >= 0; i--) {
            val = coeffs[i] + x[k] * val;
        }
        result[k] = val;
    }
}

// Initialize array with pattern
void init_array(int64_t *buf, int n, int64_t seed) {
    for (int i = 0; i < n; i++) {
        buf[i] = (i * seed + 12345) % 1000;
    }
}

int main(int argc, char *argv[]) {
    int n = ARRAY_SIZE;
    if (argc > 1) {
        n = atoi(argv[1]);
    }

    // Allocate buffers
    int64_t *a = malloc(n * sizeof(int64_t));
    int64_t *b = malloc(n * sizeof(int64_t));
    int64_t *c = malloc(n * sizeof(int64_t));

    if (!a || !b || !c) {
        fprintf(stderr, "Failed to allocate memory\n");
        return 1;
    }

    // Initialize
    init_array(a, n, 7);
    init_array(b, n, 13);

    // Run benchmarks
    vector_add(a, b, c, n);
    int64_t sum_add = vector_sum(c, n);

    vector_scale(a, 3, c, n);
    int64_t sum_scale = vector_sum(c, n);

    int64_t dot = dot_product(a, b, n);

    int64_t sum_a = vector_sum(a, n);

    saxpy(a, b, c, n, 2);
    int64_t sum_saxpy = vector_sum(c, n);

    int64_t max_a = vector_max(a, n);

    // Print results
    printf("vector_add sum: %lld\n", (long long)sum_add);
    printf("vector_scale sum: %lld\n", (long long)sum_scale);
    printf("dot_product: %lld\n", (long long)dot);
    printf("vector_sum: %lld\n", (long long)sum_a);
    printf("saxpy sum: %lld\n", (long long)sum_saxpy);
    printf("vector_max: %lld\n", (long long)max_a);

    // Cleanup
    free(a);
    free(b);
    free(c);

    return 0;
}
