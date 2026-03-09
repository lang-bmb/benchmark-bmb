// Newton's Square Root — integer square root via Newton's method
// Measures: integer division, convergence loop, branch prediction
// Workload: N=500000 values, 500 iterations

#include <stdio.h>
#include <stdint.h>

static int64_t isqrt(int64_t n) {
    if (n <= 1) return n;
    int64_t x = n;
    int64_t y = (x + 1) / 2;
    while (y < x) {
        x = y;
        y = (x + n / x) / 2;
    }
    return x;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 150;

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t val = seed % 1000000000 + 1;
            checksum += isqrt(val);
        }
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
