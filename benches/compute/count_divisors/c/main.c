// Count Divisors — count divisors for numbers 1..N
// Measures: nested loop, modulo, branch prediction
// Workload: N=30000, 500 iterations

#include <stdio.h>
#include <stdint.h>

int64_t count_divs(int64_t n) {
    int64_t count = 0;
    for (int64_t i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            count += (i * i == n) ? 1 : 2;
        }
    }
    return count;
}

int main() {
    int64_t N = 30000;
    int64_t ITERS = 500;
    int64_t checksum = 0;
    for (int64_t iter = 0; iter < ITERS; iter++) {
        int64_t sum = 0;
        for (int64_t i = 1; i <= N; i++) {
            sum += count_divs(i);
        }
        checksum += sum;
    }
    printf("%lld\n", (long long)checksum);
    return 0;
}
