// Surpass Benchmark: String Search (C baseline)
// Goal: BMB > C through compile-time pattern optimization
//
// C must perform runtime pattern analysis
// BMB's contracts can verify pattern properties at compile time

#include <stdio.h>
#include <stdint.h>

#define TEXT_SIZE 64
#define PATTERN_SIZE 3
#define ITERATIONS 10000

// Check if pattern matches at position
static inline int matches_at(int64_t* text, int64_t* pattern, int text_pos) {
    for (int i = 0; i < PATTERN_SIZE; i++) {
        if (text_pos + i >= TEXT_SIZE) return 0;
        if (text[text_pos + i] != pattern[i]) return 0;
    }
    return 1;
}

// Count pattern occurrences (optimized version)
static int64_t count_optimized(int64_t* text, int64_t* pattern) {
    int64_t count = 0;
    for (int pos = 0; pos <= TEXT_SIZE - PATTERN_SIZE; pos++) {
        if (matches_at(text, pattern, pos)) {
            count++;
        }
    }
    return count;
}

// Count pattern occurrences (with extra validation)
static int64_t count_with_validation(int64_t* text, int64_t* pattern) {
    // Must validate pattern at runtime
    if (pattern[0] <= 0) return 0;  // Invalid pattern

    int64_t count = 0;
    for (int pos = 0; pos <= TEXT_SIZE - PATTERN_SIZE; pos++) {
        if (matches_at(text, pattern, pos)) {
            count++;
        }
    }
    return count;
}

int main() {
    // Text with multiple occurrences of pattern [1, 2, 3]
    int64_t text[TEXT_SIZE] = {
        1, 2, 3, 4, 5, 1, 2, 3, 9, 10, 11, 12, 1, 2, 3, 16,
        17, 18, 1, 2, 3, 22, 23, 24, 25, 26, 1, 2, 3, 30, 31, 32,
        33, 34, 35, 36, 1, 2, 3, 40, 41, 42, 43, 44, 45, 46, 47, 48,
        1, 2, 3, 52, 53, 54, 55, 56, 57, 58, 59, 60, 1, 2, 3, 64
    };
    // Pattern to search for
    int64_t pattern[PATTERN_SIZE] = {1, 2, 3};

    int64_t total_optimized = 0;
    int64_t total_validated = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        total_optimized += count_optimized(text, pattern);
        total_validated += count_with_validation(text, pattern);
    }

    printf("Optimized: %lld, Validated: %lld\n",
           (long long)total_optimized, (long long)total_validated);
    return 0;
}
