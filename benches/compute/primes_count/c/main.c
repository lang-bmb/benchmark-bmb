// Prime Counting Benchmark
// Measures: modulo operations, nested loops, early termination

#include <stdio.h>
#include <stdint.h>

int is_prime(int64_t n) {
    if (n < 2) return 0;
    for (int64_t d = 2; d * d <= n; d++) {
        if (n % d == 0) return 0;
    }
    return 1;
}

int64_t count_primes(int64_t n) {
    int64_t count = 0;
    for (int64_t i = 2; i <= n; i++) {
        if (is_prime(i)) count++;
    }
    return count;
}

int main() {
    int64_t result = 0;
    for (int i = 0; i < 10; i++) {
        result += count_primes(50000);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
