// Fibonacci - FAIR COMPARISON benchmark
// Uses iterative O(n) algorithm matching the BMB version exactly.
// Measures: loop iteration, integer arithmetic, accumulator pattern

#include <stdio.h>
#include <stdint.h>

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
    // Run fibonacci(50) 1000000000 times for stable measurement (target: ~120ms after LICM)
    int64_t result = 0;
    for (long i = 0; i < 1000000000; i++) {
        result += fibonacci_iter(50);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
