// Zero-Overhead Proof: Overflow Check (C baseline)
// Goal: Prove BMB checked arithmetic == C unchecked (identical assembly)
//
// C approach: No overflow check (undefined behavior, but fast)
// This is what BMB's assembly should match

#include <stdio.h>
#include <stdint.h>

#define ITERATIONS 1000

// Direct arithmetic - NO overflow check (UB in C)
// BMB's contract-proven code should generate identical assembly
static inline int64_t safe_add(int64_t a, int64_t b) {
    return a + b;  // No check - trusting inputs are bounded
}

static inline int64_t safe_mul(int64_t a, int64_t b) {
    return a * b;  // No check - trusting inputs are bounded
}

// Sum 1 to n
int64_t compute_sum(int64_t n) {
    int64_t acc = 0;
    for (int64_t i = 1; i <= n; i++) {
        acc = safe_add(acc, i);
    }
    return acc;
}

// Factorial-like with bounded input
int64_t bounded_factorial(int64_t n) {
    int64_t acc = 1;
    for (int64_t i = 2; i <= n; i++) {
        acc = safe_mul(acc, i);
    }
    return acc;
}

int main() {
    int64_t total = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        int64_t sum_result = compute_sum(100);      // 5050
        int64_t fact_result = bounded_factorial(10); // 3628800
        total += sum_result + fact_result;
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
