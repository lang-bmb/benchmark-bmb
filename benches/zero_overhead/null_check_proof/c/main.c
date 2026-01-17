// Zero-Overhead Proof: Null Check (C baseline)
// Goal: Prove BMB Option<T> == C raw pointer (identical assembly)
//
// C approach: No null check (unsafe, but fast)
// This is what BMB's assembly should match

#include <stdio.h>
#include <stdint.h>

#define SIZE 100
#define ITERATIONS 100

// Direct pointer access - NO null check (unsafe in C)
// BMB's contract-proven Option code should generate identical assembly
static inline int64_t get_value(int64_t* ptr) {
    return *ptr;  // No null check - trusting caller
}

// Sum array elements using pointer arithmetic
int64_t sum_array(int64_t* arr, int64_t len) {
    int64_t sum = 0;
    for (int64_t i = 0; i < len; i++) {
        sum += get_value(&arr[i]);
    }
    return sum;
}

int main() {
    // Stack-allocated array
    int64_t arr[SIZE];

    // Initialize with values 1-100
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i + 1;
    }

    // Run iterations
    int64_t total = 0;
    for (int iter = 0; iter < ITERATIONS; iter++) {
        total += sum_array(arr, SIZE);
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
