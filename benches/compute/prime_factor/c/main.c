// Prime Factorization — trial division
// Measures: integer division, modular arithmetic, nested loops
// Workload: N=500K numbers, 5 iterations

#include <stdio.h>
#include <stdint.h>

int main(void) {
    int64_t N = 500000;
    int64_t ITERS = 5;
    int64_t checksum = 0;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t num = 2; num <= N; num++) {
            int64_t n = num;
            // Factor out 2s
            while ((n & 1) == 0) {
                checksum += 2;
                n = n / 2;
            }
            // Odd factors from 3 upward
            int64_t f = 3;
            while (f * f <= n) {
                while (n % f == 0) {
                    checksum += f;
                    n = n / f;
                }
                f += 2;
            }
            // Remaining prime factor > sqrt(num)
            if (n > 1) {
                checksum += n;
            }
        }
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
