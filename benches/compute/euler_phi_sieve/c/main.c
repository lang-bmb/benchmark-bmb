// Euler Phi Sieve — compute phi(1)..phi(N) using sieve method
// Measures: sieve traversal, integer arithmetic, prime detection
// Workload: N=5000000, 50 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t euler_phi(int64_t* phi, int64_t n) {
    // Initialize phi[i] = i
    for (int64_t i = 0; i <= n; i++) phi[i] = i;
    // Sieve: for each prime p, multiply phi[j] by (p-1)/p for all multiples j
    for (int64_t i = 2; i <= n; i++) {
        if (phi[i] == i) {
            // i is prime: phi[i] = i - 1
            phi[i] = i - 1;
            // Update all multiples of i starting from 2*i
            for (int64_t j = i * 2; j <= n; j += i) {
                phi[j] = phi[j] / i * (i - 1);
            }
        }
    }
    // Sum all totient values
    int64_t total = 0;
    for (int64_t i = 1; i <= n; i++) {
        total += phi[i];
    }
    return total;
}

int main() {
    int64_t N = 5000000;
    int64_t ITERS = 50;
    int64_t* phi = (int64_t*)malloc((N + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        checksum += euler_phi(phi, N);
    }

    printf("%lld\n", (long long)checksum);
    free(phi);
    return 0;
}
