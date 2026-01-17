// Surpass Benchmark: Sort Presorted Array (C baseline)
// Goal: BMB > C through precondition-based branch elimination
//
// C must check sortedness at runtime even when data is always sorted
// BMB's contracts can prove sortedness at compile time

#include <stdio.h>
#include <stdint.h>

#define SIZE 32
#define ITERATIONS 10000

// Check if array is sorted
static inline int is_sorted(int64_t* arr) {
    for (int i = 0; i < SIZE - 1; i++) {
        if (arr[i] > arr[i + 1]) return 0;
    }
    return 1;
}

// Sum array elements
static inline int64_t sum_array(int64_t* arr) {
    int64_t sum = 0;
    for (int i = 0; i < SIZE; i++) {
        sum += arr[i];
    }
    return sum;
}

// Process with assumption (C cannot enforce at compile time)
// Even with __builtin_assume, compiler may still generate check code
int64_t process_with_assumption(int64_t* arr) {
    // C cannot guarantee sortedness at compile time
    // __builtin_assume only hints, doesn't enforce
    return sum_array(arr);
}

// Process without assumption (must check at runtime)
int64_t process_without_assumption(int64_t* arr) {
    if (!is_sorted(arr)) {
        // Would need to sort
        return 0;
    }
    return sum_array(arr);
}

int main() {
    // Already sorted array
    int64_t arr[SIZE] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32
    };

    int64_t total_with = 0;
    int64_t total_without = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        total_with += process_with_assumption(arr);
        total_without += process_without_assumption(arr);
    }

    printf("With assumption: %lld, Without: %lld\n",
           (long long)total_with, (long long)total_without);
    return 0;
}
