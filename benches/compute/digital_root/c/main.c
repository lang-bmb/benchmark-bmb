// Digital Root Benchmark
// Measures: modulo operations, division, loops

#include <stdio.h>
#include <stdint.h>

int64_t digit_sum(int64_t n) {
    int64_t acc = 0;
    while (n > 0) {
        acc += n % 10;
        n /= 10;
    }
    return acc;
}

int64_t digital_root(int64_t n) {
    while (n >= 10) {
        n = digit_sum(n);
    }
    return n;
}

int64_t sum_digital_roots(int64_t n) {
    int64_t acc = 0;
    for (int64_t i = 1; i <= n; i++) {
        acc += digital_root(i);
    }
    return acc;
}

int main() {
    int64_t result = 0;
    for (int i = 0; i < 10; i++) {
        result += sum_digital_roots(100000);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
