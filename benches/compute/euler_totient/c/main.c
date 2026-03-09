// Euler's Totient Function — sieve-based computation
// Measures: linear sieve, integer arithmetic, array operations
// Workload: Compute totient for all numbers up to N=2M, 5 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t euler_sieve(int64_t* phi, int64_t n) {
    for (int64_t i = 0; i <= n; i++) phi[i] = i;
    for (int64_t i = 2; i <= n; i++) {
        if (phi[i] == i) {
            // i is prime
            for (int64_t j = i; j <= n; j += i) {
                phi[j] = phi[j] - phi[j] / i;
            }
        }
    }
    int64_t total = 0;
    for (int64_t i = 1; i <= n; i++) {
        total += phi[i];
    }
    return total;
}

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 5;
    int64_t* phi = (int64_t*)malloc((N + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        checksum += euler_sieve(phi, N);
    }

    printf("%lld\n", (long long)checksum);
    free(phi);
    return 0;
}