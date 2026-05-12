// Fibonacci - FAIR COMPARISON benchmark
// Uses iterative O(n) algorithm matching the BMB version exactly.
// Measures: loop iteration, integer arithmetic, accumulator pattern
// Fair: __attribute__((noinline)) prevents GCC from hoisting fibonacci_iter(50) out of loop.

#include <stdio.h>
#include <stdint.h>

__attribute__((noinline))
int64_t fibonacci_iter(int64_t n) {
    int64_t a = 0;
    int64_t b = 1;
    for (int64_t i = 0; i < n; i++) {
        int64_t temp = a + b;
        a = b;
        b = temp;
    }
    return a;
}

int main() {
    // Run fibonacci(50) 100000000 times for stable measurement (target: ~1-3s on -O2)
    // noinline prevents GCC from constant-propagating fibonacci_iter(50) across iterations.
    int64_t result = 0;
    for (long long i = 0; i < 100000000LL; i++) {
        result += fibonacci_iter(50);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
