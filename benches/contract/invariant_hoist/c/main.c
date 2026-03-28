// Invariant hoisting benchmark
// Measures: loop invariant code motion optimization
// In C: compiler (-O2+) may hoist invariant computations
// In BMB: contracts can prove invariance, enabling guaranteed hoisting

#include <stdio.h>
#include <stdint.h>

// Expensive computation that is loop-invariant
static int64_t expensive_compute(int64_t x, int64_t y) {
    int64_t result = 0;
    for (int i = 0; i < 100; i++) {
        result += (x * x + y * y) / (i + 1);
    }
    return result;
}

// Loop with invariant computation (can be hoisted)
static int64_t loop_with_invariant(int64_t n, int64_t constant_x, int64_t constant_y) {
    int64_t sum = 0;
    for (int64_t i = 0; i < n; i++) {
        // This computation is loop-invariant (depends only on constants)
        int64_t invariant = expensive_compute(constant_x, constant_y);
        sum += invariant + i;
    }
    return sum;
}

// Nested loop with outer-loop invariant
static int64_t nested_with_invariant(int64_t outer_n, int64_t inner_n, int64_t constant) {
    int64_t sum = 0;
    for (int64_t i = 0; i < outer_n; i++) {
        // Outer-loop invariant (can be hoisted outside outer loop)
        int64_t outer_invariant = expensive_compute(constant, constant);
        for (int64_t j = 0; j < inner_n; j++) {
            // Inner-loop invariant (can be hoisted to outer loop)
            int64_t inner_invariant = i * i;
            sum += outer_invariant + inner_invariant + j;
        }
    }
    return sum;
}

// Multiple invariants in same loop
static int64_t multiple_invariants(int64_t n, int64_t a, int64_t b, int64_t c) {
    int64_t sum = 0;
    for (int64_t i = 0; i < n; i++) {
        int64_t inv1 = a * a + b * b;       // Invariant 1
        int64_t inv2 = b * c + c * a;       // Invariant 2
        int64_t inv3 = expensive_compute(a, b);  // Invariant 3
        sum += inv1 + inv2 + inv3 + i;
    }
    return sum;
}

int main(void) {
    printf("Invariant Hoist Benchmark\n\n");

    // Test loop with invariant
    int64_t result1 = loop_with_invariant(100, 5, 7);
    printf("Loop with invariant: %lld\n", (long long)result1);

    // Test nested with invariant
    int64_t result2 = nested_with_invariant(10, 10, 3);
    printf("Nested with invariant: %lld\n", (long long)result2);

    // Test multiple invariants
    int64_t result3 = multiple_invariants(100, 3, 5, 7);
    printf("Multiple invariants: %lld\n", (long long)result3);

    int64_t total = result1 + result2 + result3;
    printf("\nTotal: %lld\n", (long long)total);
    printf("Done.\n");
    return 0;
}
