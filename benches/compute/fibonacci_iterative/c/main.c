// Fibonacci Iterative — compute Nth Fibonacci number iteratively
// Measures: simple loop, variable swap, addition
// Workload: fib(92) * 10000000 iterations

#include <stdio.h>
#include <stdint.h>

int64_t fib(int64_t n) {
    if (n <= 1) return n;
    int64_t a = 0, b = 1;
    for (int64_t i = 2; i <= n; i++) {
        int64_t t = a + b;
        a = b;
        b = t;
    }
    return b;
}

int main() {
    int64_t iters = 10000000;
    int64_t checksum = 0;
    for (int64_t iter = 0; iter < iters; iter++) {
        checksum += fib(92);
    }
    printf("%lld\n", (long long)checksum);
    return 0;
}
