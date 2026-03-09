// Segmented Sieve of Eratosthenes benchmark
// Measures: cache-friendly memory access, segmented iteration, byte-level sieve
// Workload: N = 10,000,000, 100 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Simple sieve up to limit, store small primes in primes_buf, return count
int64_t simple_sieve(int64_t limit, int8_t* is_prime, int64_t* primes_buf) {
    // Initialize is_prime[0..limit] to 1
    for (int64_t i = 0; i <= limit; i++) {
        is_prime[i] = 1;
    }
    is_prime[0] = 0;
    is_prime[1] = 0;

    // Sieve
    for (int64_t i = 2; i * i <= limit; i++) {
        if (is_prime[i] == 1) {
            for (int64_t j = i * i; j <= limit; j += i) {
                is_prime[j] = 0;
            }
        }
    }

    // Collect primes into primes_buf
    int64_t count = 0;
    for (int64_t i = 2; i <= limit; i++) {
        if (is_prime[i] == 1) {
            primes_buf[count] = i;
            count++;
        }
    }
    return count;
}

// Segmented sieve: count all primes up to n
int64_t segmented_sieve(int64_t n) {
    int64_t seg_size = 32768;

    // sqrt(n) - integer square root
    int64_t sqrt_n = 1;
    while ((sqrt_n + 1) * (sqrt_n + 1) <= n) {
        sqrt_n++;
    }

    // Allocate arrays
    int8_t* is_prime = (int8_t*)malloc(sqrt_n + 1);
    int64_t* primes_buf = (int64_t*)malloc((sqrt_n + 1) * sizeof(int64_t));
    int8_t* segment = (int8_t*)malloc(seg_size);

    // Step 1: Simple sieve to find small primes
    int64_t num_primes = simple_sieve(sqrt_n, is_prime, primes_buf);

    // Count primes found in simple sieve (2..sqrt_n)
    int64_t total_count = num_primes;

    // Step 2: Process segments
    int64_t lo = sqrt_n + 1;
    while (lo <= n) {
        int64_t hi_candidate = lo + seg_size - 1;
        int64_t hi = hi_candidate < n ? hi_candidate : n;
        int64_t seg_len = hi - lo + 1;

        // Initialize segment to all 1 (prime)
        for (int64_t i = 0; i < seg_len; i++) {
            segment[i] = 1;
        }

        // For each small prime, mark multiples in this segment
        for (int64_t pi = 0; pi < num_primes; pi++) {
            int64_t p = primes_buf[pi];

            // Find first multiple of p >= lo
            // start = ceil(lo / p) * p
            int64_t start_candidate = (lo / p) * p;
            int64_t start = start_candidate < lo ? start_candidate + p : start_candidate;
            // Skip p itself (p is prime)
            if (start == p) start += p;

            for (int64_t j = start; j <= hi; j += p) {
                segment[j - lo] = 0;
            }
        }

        // Count primes in this segment
        for (int64_t i = 0; i < seg_len; i++) {
            total_count += segment[i];
        }

        lo += seg_size;
    }

    free(is_prime);
    free(primes_buf);
    free(segment);
    return total_count;
}

int main() {
    int64_t n = 10000000;
    int64_t iters = 100;
    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        checksum += segmented_sieve(n);
    }
    printf("%lld\n", (long long)checksum);
    return 0;
}
