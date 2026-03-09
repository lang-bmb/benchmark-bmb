// Fibonacci Sum — sum of first N Fibonacci numbers using register carry
// Measures: pure register computation, no memory access
// Workload: N=50, 10000000 iterations

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

static int64_t fibonacci_sum(int64_t n) {
    int64_t f_prev = 0;
    int64_t f_cur = 1;
    int64_t total = 0;
    for (int64_t i = 0; i < n; i++) {
        total += f_cur;
        int64_t tmp = f_cur;
        f_cur = f_prev + f_cur;
        f_prev = tmp;
    }
    return total;
}

int main() {
    int64_t N = 50;
    int64_t ITERS = 10000000;
    int64_t checksum = 0;
    int64_t seed = 42;

    for (int64_t iter = 0; iter < ITERS; iter++) {
        seed = (seed * 1103515245 + 12345) & 0x7FFFFFFF;
        int64_t n = 20 + (seed % (N - 20 + 1));
        checksum += fibonacci_sum(n);
    }

    printf("%lld\n", (long long)(checksum % 1000000007));
    return 0;
}
