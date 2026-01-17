// Branch elimination benchmark
// Measures: dead branch removal based on value constraints
// In C: compiler may eliminate branches with constant propagation
// In BMB: contracts prove branch impossibility, enabling guaranteed elimination

#include <stdio.h>

// Always returns positive (in BMB: post ret > 0)
static long always_positive(long x) {
    if (x > 0) return x;
    return 1;  // Ensures positive
}

// Always returns non-negative (in BMB: post ret >= 0)
static long always_non_negative(long x) {
    if (x >= 0) return x;
    return 0 - x;  // abs
}

// Process with unreachable negative branch
static long process_positive(long n, long sum) {
    if (n <= 0) return sum;

    long value = always_positive(n);
    // The negative branch below is dead code (value is always > 0)
    long processed;
    if (value > 0) {
        processed = value * 2;
    } else {
        // Dead branch - never executed
        processed = 0;
    }
    return process_positive(n - 1, sum + processed);
}

// Process with multiple dead branches
static long process_abs(long n, long sum) {
    if (n <= 0) return sum;

    long value = always_non_negative(n);
    // Multiple dead branches (value is always >= 0)
    long processed;
    if (value >= 0) {
        if (value > 1000000) {
            // Unlikely but possible
            processed = value / 2;
        } else {
            processed = value * 3;
        }
    } else {
        // Dead branch - never executed
        processed = 0 - value;
    }
    return process_abs(n - 1, sum + processed);
}

// Chained conditions with provable outcomes
static long chained_positive(long x) {
    long a = always_positive(x);
    long b = always_positive(a);  // a > 0, so b > 0
    long c = always_positive(b);  // b > 0, so c > 0

    // All these negative checks are dead branches
    long result = 0;
    if (a > 0) result += a;
    if (b > 0) result += b;
    if (c > 0) result += c;

    return result;
}

// Benchmark: many operations with dead branches
static long run_benchmark(long iterations, long sum) {
    if (iterations <= 0) return sum;

    long r1 = process_positive(100, 0);
    long r2 = process_abs(100, 0);
    long r3 = chained_positive(iterations);

    return run_benchmark(iterations - 1, sum + r1 + r2 + r3);
}

int main(void) {
    printf("Branch Elimination Benchmark\n\n");

    long result1 = process_positive(100, 0);
    printf("Process positive: %ld\n", result1);

    long result2 = process_abs(100, 0);
    printf("Process abs: %ld\n", result2);

    long result3 = chained_positive(50);
    printf("Chained positive: %ld\n", result3);

    // Benchmark
    long bench = run_benchmark(100, 0);
    printf("\nBenchmark (100 iterations): %ld\n", bench);

    printf("Done.\n");
    return 0;
}
