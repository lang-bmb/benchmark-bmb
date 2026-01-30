// Sum of Squares Benchmark
// Measures: arithmetic operations, loop performance

#include <stdio.h>
#include <stdint.h>

int64_t sum_squares(int64_t n) {
    int64_t acc = 0;
    for (int64_t i = 1; i <= n; i++) {
        acc += i * i;
    }
    return acc;
}

int main() {
    int64_t result = 0;
    for (int i = 0; i < 1000; i++) {
        result += sum_squares(100000);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
