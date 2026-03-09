// Sum of Primes — sum all primes up to N using trial division
// Measures: nested loop, modulo, branch prediction
// Workload: sum primes up to 50000, 3000 iterations

#include <stdio.h>
#include <stdint.h>

int64_t is_prime(int64_t n) {
    if (n < 2) return 0;
    if (n < 4) return 1;
    if (n % 2 == 0) return 0;
    for (int64_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int main() {
    int64_t LIMIT = 50000;
    int64_t ITERS = 3000;
    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t sum = 0;
        for (int64_t n = 2; n <= LIMIT; n++) {
            if (is_prime(n)) sum += n;
        }
        checksum += sum;
    }
    printf("%lld\n", (long long)checksum);
    return 0;
}
