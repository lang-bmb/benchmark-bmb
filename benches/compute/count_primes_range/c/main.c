// Count Primes in Range — segmented counting using sieve
// Measures: sieve computation, sequential access, range queries
// Workload: count primes in [1, 10^6], 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t count_primes(int64_t limit, int64_t* sieve) {
    for (int64_t i = 0; i <= limit; i++) sieve[i] = 1;
    sieve[0] = 0;
    sieve[1] = 0;
    for (int64_t i = 2; i * i <= limit; i++) {
        if (sieve[i]) {
            for (int64_t j = i * i; j <= limit; j += i) {
                sieve[j] = 0;
            }
        }
    }
    int64_t count = 0;
    for (int64_t i = 2; i <= limit; i++) {
        count += sieve[i];
    }
    return count;
}

int main() {
    int64_t LIMIT = 1000000;
    int64_t ITERS = 500;
    int64_t* sieve = (int64_t*)malloc((LIMIT + 1) * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t lim = LIMIT - iter * 100;
        checksum += count_primes(lim, sieve);
    }

    printf("%lld\n", (long long)checksum);
    free(sieve);
    return 0;
}
