// Zero-Overhead Proof: Aliasing Analysis (C baseline)
// Goal: Prove BMB can enable SIMD optimizations through aliasing guarantees
//
// C approach: Use restrict keyword to hint no aliasing
// BMB's functional semantics should match or exceed this

#include <stdio.h>
#include <stdint.h>

#define SIZE 10
#define ITERATIONS 10000

// Vector addition with restrict - allows SIMD optimization
static inline int64_t vec_add_element(int64_t a, int64_t b) {
    return a + b;
}

// Sum two arrays element-wise
int64_t sum_arrays(const int64_t* restrict a, const int64_t* restrict b) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        acc += vec_add_element(a[i], b[i]);
    }
    return acc;
}

// Dot product - classic SIMD-friendly operation
int64_t dot_product(const int64_t* restrict a, const int64_t* restrict b) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        acc += a[i] * b[i];
    }
    return acc;
}

int main() {
    int64_t a[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int64_t b[SIZE] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    int64_t total = 0;
    for (int iter = 0; iter < ITERATIONS; iter++) {
        int64_t sum_result = sum_arrays(a, b);
        int64_t dot_result = dot_product(a, b);
        total += sum_result + dot_result;
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
