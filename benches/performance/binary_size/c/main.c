// Binary Size Benchmark
// Measures: Executable size for equivalent functionality
//
// This benchmark is run differently than others:
// - We measure the size of the compiled executable
// - Contains the same functionality as other languages for fair comparison

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int64_t abs_val(int64_t x) { return x < 0 ? -x : x; }

int64_t gcd(int64_t a, int64_t b) {
    return b == 0 ? a : gcd(b, a % b);
}

int64_t fibonacci(int64_t n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

bool is_prime_check(int64_t n, int64_t d) {
    if (d * d > n) return true;
    if (n % d == 0) return false;
    return is_prime_check(n, d + 2);
}

bool is_prime(int64_t n) {
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    return is_prime_check(n, 3);
}

int main() {
    int64_t result = gcd(48, 18) + fibonacci(10) + (is_prime(17) ? 1 : 0);
    printf("%lld\n", (long long)result);
    return 0;
}
