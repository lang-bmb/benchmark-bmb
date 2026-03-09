// Harmonic Sum — compute sum of 1/1 + 1/2 + ... + 1/N using integer arithmetic
// Measures: division, accumulation, loop
// Workload: N=10000, 500000 iterations

#include <stdio.h>
#include <stdint.h>

int main() {
    int64_t N = 10000;
    int64_t ITERS = 500000;
    int64_t scale = 1000000000;

    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t sum = 0;
        for (int64_t i = 1; i <= N; i++) {
            sum += scale / i;
        }
        checksum += sum;
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
