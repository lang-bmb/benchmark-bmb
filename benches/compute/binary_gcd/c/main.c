// Binary GCD (Stein's algorithm) — GCD using subtraction and division by 2
// Measures: bit operations, branch prediction, integer arithmetic
// Workload: 500000 pairs, 200 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t binary_gcd(int64_t u, int64_t v) {
    if (u == 0) return v;
    if (v == 0) return u;
    int64_t shift = 0;
    while (((u | v) & 1) == 0) { u >>= 1; v >>= 1; shift++; }
    while ((u & 1) == 0) u >>= 1;
    do {
        while ((v & 1) == 0) v >>= 1;
        if (u > v) { int64_t t = u; u = v; v = t; }
        v = v - u;
    } while (v != 0);
    return u << shift;
}

int main() {
    int64_t N = 500000;
    int64_t ITERS = 50;

    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        for (int64_t i = 0; i < N; i++) {
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t a = (seed % 1000000) + 1;
            seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
            int64_t b = (seed % 1000000) + 1;
            checksum += binary_gcd(a, b);
        }
    }

    printf("%lld\n", (long long)checksum);
    return 0;
}
