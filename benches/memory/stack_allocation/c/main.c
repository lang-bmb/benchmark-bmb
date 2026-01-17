// Memory Benchmark: Stack Allocation (C baseline)
// Goal: Measure stack variable allocation and access performance
//
// Tests creating and accessing many local variables

#include <stdio.h>
#include <stdint.h>

#define ITERATIONS 1000
#define DEPTH 50

// Create multiple local variables and compute with them
static inline int64_t compute_locals(int64_t x) {
    int64_t a = x + 1;
    int64_t b = a * 2;
    int64_t c = b - 3;
    int64_t d = c + a;
    int64_t e = d * b;
    int64_t f = e - c;
    int64_t g = f + d;
    int64_t h = g * 2;
    return a + b + c + d + e + f + g + h;
}

// Nested function calls creating deep stack
int64_t deep_stack(int64_t depth, int64_t acc) {
    if (depth <= 0) {
        return acc;
    }
    int64_t local1 = acc + depth;
    int64_t local2 = local1 * 2;
    int64_t local3 = compute_locals(local2);
    return deep_stack(depth - 1, local3);
}

int main() {
    int64_t total = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        total += deep_stack(DEPTH, 0);
    }

    printf("Total: %lld\n", (long long)total);
    return 0;
}
