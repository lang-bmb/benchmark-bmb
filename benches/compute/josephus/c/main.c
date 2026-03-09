// Josephus Problem Benchmark
// Measures: modular arithmetic, tight loop performance
// O(n) formula: J(1)=0, J(n)=(J(n-1)+k)%n
// Workload: n=10000000, k=2..101 (100 iterations)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t josephus(int64_t n, int64_t k) {
    int64_t pos = 0;
    for (int64_t i = 2; i <= n; i++) {
        pos = (pos + k) % i;
    }
    return pos;
}

int main() {
    int64_t n = 10000000;
    int64_t checksum = 0;
    for (int64_t k = 2; k <= 101; k++) {
        checksum += josephus(n, k);
    }
    printf("%lld\n", (long long)checksum);
    return 0;
}
