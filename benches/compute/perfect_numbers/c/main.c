// Perfect Numbers Benchmark
// Measures: divisor finding, accumulation, nested loops

#include <stdio.h>
#include <stdint.h>

int64_t sum_divisors(int64_t n) {
    int64_t acc = 0;
    for (int64_t d = 1; d < n; d++) {
        if (n % d == 0) acc += d;
    }
    return acc;
}

int is_perfect(int64_t n) {
    if (n <= 1) return 0;
    return sum_divisors(n) == n;
}

int64_t count_perfect(int64_t n) {
    int64_t count = 0;
    for (int64_t i = 2; i <= n; i++) {
        if (is_perfect(i)) count++;
    }
    return count;
}

int main() {
    int64_t result = 0;
    for (int i = 0; i < 10; i++) {
        result += count_perfect(10000);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
