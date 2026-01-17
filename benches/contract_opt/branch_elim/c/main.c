// Contract Optimization Proof: Branch Elimination (C baseline)
// Goal: Compare branchy vs branchless code paths

#include <stdio.h>
#include <stdint.h>

#define SIZE 32
#define ITERATIONS 1000

// UNCHECKED: Assumes positive input (branchless)
static inline int64_t abs_unchecked(int64_t x) {
    return x;  // Assumes x >= 0, no branch needed
}

// CHECKED: Must handle both positive and negative
static inline int64_t abs_checked(int64_t x) {
    return (x >= 0) ? x : -x;
}

// UNCHECKED: Assumes valid divisor
static inline int64_t safe_divide_unchecked(int64_t a, int64_t b) {
    return a / b;  // Assumes b > 0
}

// CHECKED: Must validate divisor
static inline int64_t safe_divide_checked(int64_t a, int64_t b) {
    if (b == 0) return 0;
    if (a < 0) return 0;
    return a / b;
}

// Compute with unchecked operations
int64_t compute_unchecked(int64_t* values) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        int64_t abs_val = abs_unchecked(values[i]);
        int64_t divided = safe_divide_unchecked(abs_val, 2);
        acc += divided;
    }
    return acc;
}

// Compute with checked operations
int64_t compute_checked(int64_t* values) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        int64_t abs_val = abs_checked(values[i]);
        int64_t divided = safe_divide_checked(abs_val, 2);
        acc += divided;
    }
    return acc;
}

int main() {
    int64_t values[SIZE];
    for (int i = 0; i < SIZE; i++) {
        values[i] = i + 1;
    }

    int64_t total_unchecked = 0;
    int64_t total_checked = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        total_unchecked += compute_unchecked(values);
        total_checked += compute_checked(values);
    }

    printf("Unchecked: %lld, Checked: %lld\n",
           (long long)total_unchecked, (long long)total_checked);
    return 0;
}
