// Contract Optimization Proof: Null Elimination (C baseline)
// Goal: Compare null-checked vs unchecked value processing

#include <stdio.h>
#include <stdint.h>

#define SIZE 50
#define ITERATIONS 1000

// UNCHECKED: Assumes value is valid (like contract-proven)
static inline int64_t process_unchecked(int64_t value, int64_t multiplier) {
    return value * multiplier;
}

// CHECKED: Runtime null validation
static inline int64_t process_checked(int64_t value, int64_t multiplier) {
    if (value == -1) return 0;  // Null check
    if (multiplier <= 0) return 0;
    return value * multiplier;
}

// Sum with unchecked processing
int64_t sum_unchecked(int64_t* arr, int64_t multiplier) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        acc += process_unchecked(arr[i], multiplier);
    }
    return acc;
}

// Sum with checked processing
int64_t sum_checked(int64_t* arr, int64_t multiplier) {
    int64_t acc = 0;
    for (int i = 0; i < SIZE; i++) {
        acc += process_checked(arr[i], multiplier);
    }
    return acc;
}

int main() {
    int64_t arr[SIZE];
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    int64_t total_unchecked = 0;
    int64_t total_checked = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        total_unchecked += sum_unchecked(arr, 2);
        total_checked += sum_checked(arr, 2);
    }

    printf("Unchecked: %lld, Checked: %lld\n",
           (long long)total_unchecked, (long long)total_checked);
    return 0;
}
