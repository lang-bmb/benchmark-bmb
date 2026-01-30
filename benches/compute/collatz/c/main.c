// Collatz Conjecture Benchmark
// Measures: branching, integer operations, loop performance

#include <stdio.h>
#include <stdint.h>

int64_t collatz_length(int64_t n) {
    int64_t steps = 0;
    while (n > 1) {
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = 3 * n + 1;
        }
        steps++;
    }
    return steps;
}

int64_t sum_collatz_lengths(int64_t start, int64_t end) {
    int64_t acc = 0;
    for (int64_t i = start; i <= end; i++) {
        acc += collatz_length(i);
    }
    return acc;
}

int main() {
    int64_t result = 0;
    for (int i = 0; i < 10; i++) {
        result += sum_collatz_lengths(1, 10000);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
