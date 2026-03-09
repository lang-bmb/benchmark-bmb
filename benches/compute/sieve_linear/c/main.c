// Sieve Linear — linear sieve of Eratosthenes
// Measures: sequential writes, random access, branch prediction
// Workload: sieve up to 2000000, 500 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main() {
    int64_t N = 2000000;
    int64_t ITERS = 500;
    int64_t* is_prime = (int64_t*)malloc(N * sizeof(int64_t));

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) is_prime[i] = 1;
        is_prime[0] = 0;
        is_prime[1] = 0;

        for (int64_t i = 2; i * i < N; i++) {
            if (is_prime[i]) {
                for (int64_t j = i * i; j < N; j += i) {
                    is_prime[j] = 0;
                }
            }
        }

        int64_t count = 0;
        for (int64_t i = 0; i < N; i++) count += is_prime[i];
        checksum += count;
    }

    printf("%lld\n", (long long)checksum);
    free(is_prime);
    return 0;
}
