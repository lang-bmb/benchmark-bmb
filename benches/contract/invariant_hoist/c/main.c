// Invariant hoisting benchmark
// Measures: loop invariant code motion optimization
// In C: compiler (-O2+) may hoist invariant computations
// In BMB: contracts can prove invariance, enabling guaranteed hoisting

#include <stdio.h>

// Expensive computation that is loop-invariant
static long expensive_compute(long x, long y) {
    long result = 0;
    for (int i = 0; i < 100; i++) {
        result += (x * x + y * y) / (i + 1);
    }
    return result;
}

// Loop with invariant computation (can be hoisted)
static long loop_with_invariant(long n, long constant_x, long constant_y) {
    long sum = 0;
    for (long i = 0; i < n; i++) {
        // This computation is loop-invariant (depends only on constants)
        long invariant = expensive_compute(constant_x, constant_y);
        sum += invariant + i;
    }
    return sum;
}

// Nested loop with outer-loop invariant
static long nested_with_invariant(long outer_n, long inner_n, long constant) {
    long sum = 0;
    for (long i = 0; i < outer_n; i++) {
        // Outer-loop invariant (can be hoisted outside outer loop)
        long outer_invariant = expensive_compute(constant, constant);
        for (long j = 0; j < inner_n; j++) {
            // Inner-loop invariant (can be hoisted to outer loop)
            long inner_invariant = i * i;
            sum += outer_invariant + inner_invariant + j;
        }
    }
    return sum;
}

// Multiple invariants in same loop
static long multiple_invariants(long n, long a, long b, long c) {
    long sum = 0;
    for (long i = 0; i < n; i++) {
        long inv1 = a * a + b * b;       // Invariant 1
        long inv2 = b * c + c * a;       // Invariant 2
        long inv3 = expensive_compute(a, b);  // Invariant 3
        sum += inv1 + inv2 + inv3 + i;
    }
    return sum;
}

int main(void) {
    printf("Invariant Hoist Benchmark\n\n");

    // Test loop with invariant
    long result1 = loop_with_invariant(100, 5, 7);
    printf("Loop with invariant: %ld\n", result1);

    // Test nested with invariant
    long result2 = nested_with_invariant(10, 10, 3);
    printf("Nested with invariant: %ld\n", result2);

    // Test multiple invariants
    long result3 = multiple_invariants(100, 3, 5, 7);
    printf("Multiple invariants: %ld\n", result3);

    long total = result1 + result2 + result3;
    printf("\nTotal: %ld\n", total);
    printf("Done.\n");
    return 0;
}
