// Ackermann Function Benchmark
// Measures: deep recursion, function call overhead

#include <stdio.h>
#include <stdint.h>

int64_t ackermann(int64_t m, int64_t n) {
    if (m == 0) return n + 1;
    if (n == 0) return ackermann(m - 1, 1);
    return ackermann(m - 1, ackermann(m, n - 1));
}

int main() {
    int64_t result = 0;
    for (int i = 0; i < 1000; i++) {
        result += ackermann(3, 10);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
