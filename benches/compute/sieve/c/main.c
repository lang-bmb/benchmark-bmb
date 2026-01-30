// Sieve of Eratosthenes - Prime number benchmark
// Measures: array operations, bit manipulation, loop performance

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int64_t sieve(int64_t n) {
    int8_t* arr = (int8_t*)malloc(n + 1);

    // Initialize all to 1
    for (int64_t i = 0; i <= n; i++) {
        arr[i] = 1;
    }

    arr[0] = 0;
    arr[1] = 0;

    // Sieve
    for (int64_t i = 2; i * i <= n; i++) {
        if (arr[i]) {
            for (int64_t j = i * i; j <= n; j += i) {
                arr[j] = 0;
            }
        }
    }

    // Count primes
    int64_t count = 0;
    for (int64_t i = 2; i <= n; i++) {
        if (arr[i]) count++;
    }

    free(arr);
    return count;
}

int main() {
    // 1500 iterations for stable measurement (target: ~140ms)
    int64_t result = 0;
    for (int i = 0; i < 1500; i++) {
        result += sieve(100000);
    }
    printf("%lld\n", (long long)result);
    return 0;
}
