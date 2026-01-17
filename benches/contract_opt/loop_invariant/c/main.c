// Contract Optimization Proof: Loop Invariant Hoisting (C baseline)
// Goal: Compare loop with hoistable vs non-hoistable computations

#include <stdio.h>
#include <stdint.h>

#define SIZE 32
#define ITERATIONS 1000

// Pure function - can be hoisted
__attribute__((const))
static inline int64_t compute_factor(int64_t base, int64_t power) {
    int64_t result = 1;
    for (int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}

// Impure simulation - depends on loop variable
static inline int64_t compute_factor_impure(int64_t base, int64_t power, int64_t check) {
    if (check < 0) return 0;  // Dependency on external state
    int64_t result = 1;
    for (int i = 0; i < power; i++) {
        result *= base;
    }
    return result;
}

// Loop with hoistable computation
int64_t loop_with_hoistable(int64_t* arr, int64_t factor_base, int64_t factor_power) {
    int64_t acc = 0;
    // Compiler should hoist this out of the loop
    int64_t factor = compute_factor(factor_base, factor_power);
    for (int i = 0; i < SIZE; i++) {
        acc += arr[i] * factor;
    }
    return acc;
}

// Loop with non-hoistable computation
int64_t loop_without_hoistable(int64_t* arr, int64_t factor_base, int64_t factor_power) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        // Depends on loop index, cannot be hoisted
        int64_t factor = compute_factor_impure(factor_base, factor_power, i);
        acc += arr[i] * factor;
    }
    return acc;
}

int main() {
    int64_t arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    int64_t total_hoistable = 0;
    int64_t total_non_hoistable = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        total_hoistable += loop_with_hoistable(arr, 2, 3);
        total_non_hoistable += loop_without_hoistable(arr, 2, 3);
    }

    printf("Hoistable: %lld, Non-hoistable: %lld\n",
           (long long)total_hoistable, (long long)total_non_hoistable);
    return 0;
}
