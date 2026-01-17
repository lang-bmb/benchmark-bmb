// Zero-Overhead Proof: Bounds Check (C baseline)
// Goal: Prove BMB safe code == C unsafe code (identical assembly)
//
// C approach: No bounds check (unsafe, but fast)
// This is what BMB's assembly should match

#include <stdio.h>
#include <stdint.h>

#define SIZE 1000
#define ITERATIONS 10000

// Direct array access - NO bounds check (unsafe in C)
// BMB's contract-proven code should generate identical assembly
static inline int64_t get_element(int64_t* arr, int64_t idx) {
    return arr[idx];  // No check - trusting caller
}

// Sum array elements
int64_t sum_array(int64_t* arr) {
    int64_t sum = 0;
    for (int64_t i = 0; i < SIZE; i++) {
        sum += get_element(arr, i);
    }
    return sum;
}

int main() {
    // Stack-allocated array
    int64_t arr[SIZE] = {0};

    // Initialize with values
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    // Run iterations
    int64_t total = 0;
    for (int iter = 0; iter < ITERATIONS; iter++) {
        total += sum_array(arr);
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
