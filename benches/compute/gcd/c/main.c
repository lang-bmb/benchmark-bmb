// GCD (Greatest Common Divisor) Benchmark
// Measures: recursion, modulo operations, integer arithmetic

#include <stdio.h>
#include <stdint.h>

int64_t gcd(int64_t a, int64_t b) {
    while (b != 0) {
        int64_t t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int64_t sum_gcds(int64_t n) {
    int64_t acc = 0;
    for (int64_t i = 1; i <= n; i++) {
        for (int64_t j = 1; j <= n; j++) {
            acc += gcd(i, j);
        }
    }
    return acc;
}

int main() {
    int64_t result = 0;
    for (int i = 0; i < 10; i++) {
        result += sum_gcds(300);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
