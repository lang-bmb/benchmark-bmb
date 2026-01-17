// Contract Optimization Proof: Bounds Elimination (C baseline)
// Goal: Compare bounds-checked vs unchecked array access
//
// Two versions: unchecked (assumes valid bounds)
//              checked (runtime validation)

#include <stdio.h>
#include <stdint.h>

#define SIZE 100
#define ITERATIONS 1000

// UNCHECKED: Assumes bounds are valid (like contract-proven)
int64_t sum_unchecked(int64_t* arr, int64_t start, int64_t end) {
    int64_t acc = 0;
    for (int64_t i = start; i < end; i++) {
        acc += arr[i];  // No bounds check
    }
    return acc;
}

// CHECKED: Runtime bounds validation
int64_t sum_checked(int64_t* arr, int64_t start, int64_t end) {
    if (start < 0) return 0;
    if (end > SIZE) return 0;
    if (start >= end) return 0;

    int64_t acc = 0;
    for (int64_t i = start; i < end; i++) {
        // Redundant check that compiler may or may not eliminate
        if (i >= 0 && i < SIZE) {
            acc += arr[i];
        }
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
        total_unchecked += sum_unchecked(arr, 0, SIZE);
        total_checked += sum_checked(arr, 0, SIZE);
    }

    printf("Unchecked: %lld, Checked: %lld\n",
           (long long)total_unchecked, (long long)total_checked);
    return 0;
}
