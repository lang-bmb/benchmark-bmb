// Sum of Divisors — compute sum of divisors for each number
// Measures: integer division, nested loops, modular arithmetic
// Workload: N=50000, 200 iterations

#include <stdio.h>
#include <stdint.h>

static int64_t sum_div(int64_t n) {
    int64_t s = 0;
    for (int64_t d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            s += d;
            if (d != n / d) s += n / d;
        }
    }
    return s;
}

int main() {
    int64_t N = 50000;
    int64_t ITERS = 200;

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 1; i <= N; i++) {
            checksum += sum_div(i);
        }
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
