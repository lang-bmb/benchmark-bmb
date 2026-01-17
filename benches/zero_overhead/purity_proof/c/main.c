// Zero-Overhead Proof: Purity Optimization (C baseline)
// Goal: Prove BMB pure functions enable CSE and hoisting optimizations
//
// C approach: Use __attribute__((const)) to mark pure functions
// BMB's 'pure' keyword should enable equivalent optimizations

#include <stdio.h>
#include <stdint.h>

#define ITERATIONS 1000

// Pure computation - marked for CSE
__attribute__((const))
static inline int64_t compute_value(int64_t x) {
    return x * x + x * 2 + 1;
}

// Expensive pure computation
__attribute__((const))
static inline int64_t expensive_pure(int64_t n) {
    return compute_value(n) + compute_value(n) + compute_value(n);
}

// Sum with repeated pure calls
int64_t sum_with_pure(int64_t n) {
    int64_t acc = 0;
    for (int64_t i = n; i > 0; i--) {
        // Same pure call twice - CSE should merge
        int64_t v1 = compute_value(i);
        int64_t v2 = compute_value(i);
        acc += v1 + v2;
    }
    return acc;
}

// Loop with invariant pure call
int64_t loop_with_invariant(int64_t iterations, int64_t constant) {
    int64_t acc = 0;
    for (int64_t i = 0; i < iterations; i++) {
        // expensive_pure(constant) is loop-invariant
        acc += expensive_pure(constant);
    }
    return acc;
}

int main() {
    int64_t total = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        int64_t sum_result = sum_with_pure(20);
        int64_t loop_result = loop_with_invariant(100, 25);
        total += sum_result + loop_result;
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
