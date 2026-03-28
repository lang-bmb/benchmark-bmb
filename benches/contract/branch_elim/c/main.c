// Branch elimination benchmark
// Measures: dead branch removal based on value constraints
// In C: compiler may eliminate branches with constant propagation
// In BMB: contracts prove branch impossibility, enabling guaranteed elimination

#include <stdio.h>
#include <stdint.h>

// Always returns positive (in BMB: post ret > 0)
static int64_t always_positive(int64_t x) {
    if (x > 0) return x;
    return 1;  // Ensures positive
}

// Always returns non-negative (in BMB: post ret >= 0)
static int64_t always_non_negative(int64_t x) {
    if (x >= 0) return x;
    return 0 - x;  // abs
}

// Process with unreachable negative branch
static int64_t process_positive(int64_t n, int64_t sum) {
    if (n <= 0) return sum;

    int64_t value = always_positive(n);
    // The negative branch below is dead code (value is always > 0)
    int64_t processed;
    if (value > 0) {
        processed = value * 2;
    } else {
        // Dead branch - never executed
        processed = 0;
    }
    return process_positive(n - 1, sum + processed);
}

// Process with multiple dead branches
static int64_t process_abs(int64_t n, int64_t sum) {
    if (n <= 0) return sum;

    int64_t value = always_non_negative(n);
    // Multiple dead branches (value is always >= 0)
    int64_t processed;
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
static int64_t chained_positive(int64_t x) {
    int64_t a = always_positive(x);
    int64_t b = always_positive(a);  // a > 0, so b > 0
    int64_t c = always_positive(b);  // b > 0, so c > 0

    // All these negative checks are dead branches
    int64_t result = 0;
    if (a > 0) result += a;
    if (b > 0) result += b;
    if (c > 0) result += c;

    return result;
}

// Benchmark: many operations with dead branches
static int64_t run_benchmark(int64_t iterations, int64_t sum) {
    if (iterations <= 0) return sum;

    int64_t r1 = process_positive(100, 0);
    int64_t r2 = process_abs(100, 0);
    int64_t r3 = chained_positive(iterations);

    return run_benchmark(iterations - 1, sum + r1 + r2 + r3);
}

int main(void) {
    printf("Branch Elimination Benchmark\n\n");

    int64_t result1 = process_positive(100, 0);
    printf("Process positive: %lld\n", (long long)result1);

    int64_t result2 = process_abs(100, 0);
    printf("Process abs: %lld\n", (long long)result2);

    int64_t result3 = chained_positive(50);
    printf("Chained positive: %lld\n", (long long)result3);

    // Benchmark
    int64_t bench = run_benchmark(100, 0);
    printf("\nBenchmark (100 iterations): %lld\n", (long long)bench);

    printf("Done.\n");
    return 0;
}
